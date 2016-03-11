(*
 * Copyright yutopp 2015 - .
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *)

module type CONTEXT_TYPE =
  sig
    type ir_context_t
    type ir_builder_t
    type ir_module_t
    type ir_intrinsics

    type ('ty, 'ctx) value_record_t
  end

module Make (Cgt : CONTEXT_TYPE) =
  struct
    module IdOrderedType =
      struct
        type t = Env.id_t
        let compare = Num.compare_num
      end
    module IdSet = Set.Make(IdOrderedType)

    type ('env, 'ty, 'v) t = {
      mutable ir_context        : Cgt.ir_context_t;
      mutable ir_builder        : Cgt.ir_builder_t;
      mutable ir_module         : Cgt.ir_module_t;
      intrinsics                : Cgt.ir_intrinsics;

      env_to_record_tbl         : (Env.id_t, ('env, 'ty, 'v) value_t) Hashtbl.t;
      name_to_record_tbl        : (string, ('env, 'ty, 'v) value_t) Hashtbl.t;

      mutable defined_env       : IdSet.t;
      type_sets                 : 'env Type_sets.type_sets_t option;
      uni_map                   : ('ty, 'v) Unification.t option;
    }
     and ('env, 'ty, 'v) value_t = ('ty, (('env, 'ty, 'v) t)) Cgt.value_record_t


    let init ~ir_context
             ~ir_builder
             ~ir_module
             ~ir_intrinsics
             ~type_sets
             ~uni_map =
      {
        ir_context = ir_context;
        ir_builder = ir_builder;
        ir_module = ir_module;
        intrinsics = ir_intrinsics;

        env_to_record_tbl = Hashtbl.create 32;
        name_to_record_tbl = Hashtbl.create 32;

        defined_env = IdSet.empty;
        type_sets = type_sets;
        uni_map = uni_map;
      }

    (**)
    let mark_env_as_defined ctx env =
      ctx.defined_env <- (IdSet.add env.Env.env_id ctx.defined_env)

    let is_env_defined ctx env =
      IdSet.mem env.Env.env_id ctx.defined_env


    (**)
    let bind_val_to_env ctx value env =
      Hashtbl.add ctx.env_to_record_tbl env.Env.env_id value

    let find_val_by_env ctx env =
      Hashtbl.find ctx.env_to_record_tbl env.Env.env_id


    (**)
    let bind_val_to_name ctx value name =
      Hashtbl.add ctx.name_to_record_tbl name value

    let find_val_by_name ctx name =
      Hashtbl.find ctx.name_to_record_tbl name
  end