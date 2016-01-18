open Batteries

type checked_state =
    InComplete
  | Checking
  | Complete

module Kind =
  struct
    type t =
        Module
      | Class
      | Function
      | MultiSet of t
  end

type builtin_t =
    TypeTy
  | Int32Ty

type 'ast env_record_t =
  | Root of 'ast lookup_table_t
  | MultiSet of 'ast multiset_record

  | Module of 'ast lookup_table_t * module_record
  | Function of 'ast lookup_table_t
  | Class of 'ast lookup_table_t

  | Dummy

 and 'ast env_t = {
   parent_env       : 'ast env_t option;
   er               : 'ast env_record_t;
   mutable state    : checked_state;

   mutable rel_node : 'ast option;
 }

 and 'ast name_env_mapping = (string, 'ast env_t) Hashtbl.t

 and 'ast lookup_table_t = {
   scope            : 'ast name_env_mapping;
 }

 and 'ast multiset_record = {
   ms_kind                  : Kind.t;
   mutable ms_candidates    : 'ast env_t list;
 }


 and module_record = {
   mod_name     : string;
 }


let get_lookup_record e =
  let { er = er; _ } = e in
  match er with
  | Root (r) -> r
  | Module (r, _) -> r
  | Function (r) -> r
  | Class (r) -> r
  | _ -> failwith "has no common record"

let get_symbol_table e =
  let lt = get_lookup_record e in
  lt.scope


let is_root e =
  let { er = er; _ } = e in
  match er with
    Root _  -> true
  | _       -> false

let parent_env e =
  if is_root e then
    failwith "root env has no parent env"
  else
    let { parent_env = opt_penv } = e in
    match opt_penv with
      Some penv -> penv
    | None -> failwith ""

(* *)
let find_on_env e name =
  let t = get_symbol_table e in
  try
    Some (Hashtbl.find t name)
  with
    Not_found -> None

(*  *)
let rec lookup e name =
  let target = find_on_env e name in
  match target with
    Some _ as te -> te
  | None -> if is_root e then
              None
            else
              let penv = parent_env e in
              lookup penv name

(*  *)
let add (name : string) (e : 'a env_t) (target_env : 'a env_t) =
  let t = get_symbol_table target_env in
  Hashtbl.add t name e


let empty_lookup_table () =
  {
    scope = Hashtbl.create 10;
  }

let create_env parent_env er =
  {
    parent_env = Some parent_env;
    er = er;
    state = InComplete;
    rel_node = None;
  }

(**)
let is_checked e =
  let { state = s; _ } = e in
  s = Checking || s = Complete

let is_incomplete e =
  not (is_checked e)


let update_status e ns =
  e.state <- ns


(**)
let update_rel_ast e node =
  e.rel_node <- Some node

let get_rel_ast e =
  Option.get e.rel_node


(**)
let make_root_env () =
  let tbl = empty_lookup_table () in
  {
    parent_env = None;
    er = Root (tbl);
    state = Complete;
    rel_node = None;
  }

let find_or_create_multi_env env name k =
  let oe = find_on_env env name in
  match oe with
  (* *)
  | Some ({ er = (MultiSet { ms_kind = k; _ }); _} as e) ->
     e

  (* *)
  | None ->
     create_env env (MultiSet {
                         ms_kind = k;
                         ms_candidates = [];
                       })

  | _ -> failwith "multienv is not found"


module MultiSetOp =
  struct
    let add_candidates menv env =
      let { er = mer; _ } = menv in
      match mer with
      | MultiSet (record) ->
         begin
           (* add env to lists as candidates *)
           record.ms_candidates <- env :: record.ms_candidates;
           ()
         end
      | _ -> failwith "can not add candidate"
  end


module ClassOp =
  struct
  end
