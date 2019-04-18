(*
 * Copyright yutopp 2018 - .
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *)

open! Base

let () =
  let opts = Flags.parse () in
  let opts = match Flags.validate opts with
    | Ok opts ->
       opts
    | Error _ ->
       Stdio.eprintf "ERR: args\n"; (* TODO: fix *)
       Caml.exit 1
  in

  let filename = Flags.input_files opts |> List.hd |> Option.value ~default:"DUMMY" in
  Stdio.eprintf "filename: %s\n" filename;

  let r =
    let open Result.Let_syntax in
    let%bind node = Rillc.Syntax.parse_from_file filename in
    Stdio.eprintf "AST = \n%s\n" (Rillc.Syntax.Ast.sexp_of_t node |> Sexplib.Sexp.to_string_hum ~indent:2);
    let%bind (tnode, ctx) = Rillc.Sema.sem node in
    Stdio.eprintf "SEMA = \n%s\n" (Rillc.Hir.sexp_of_t tnode |> Sexp.to_string_hum ~indent:2);
    let%bind k_form = Rillc.Rir.KNorm.generate tnode in
    Stdio.eprintf "K form = \n%s\n" (Rillc.Rir.KNorm.sexp_of_t k_form |> Sexp.to_string_hum ~indent:2);
    let%bind rir = Rillc.Rir.Trans.transform k_form in
    Stdio.eprintf "RIR = \n%s\n" (Rillc.Rir.Term.sexp_of_t rir |> Sexp.to_string_hum ~indent:2);
    let cctx = Rillc.Codegen_llvm.create_context () in
    let%bind cmod = Rillc.Codegen_llvm.create_module cctx rir in
    Stdio.eprintf "LLVM = \n%s\n" (cmod |> Rillc.Codegen_llvm.debug_string_of);
    rir |> return
  in
  match r with
  | Ok _ ->
     Stdio.eprintf "OK"
  | Error d ->
     Stdio.eprintf "-> %s\n" (Rillc.Diagnostics.to_string d)