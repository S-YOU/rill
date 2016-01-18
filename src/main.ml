let () =
  let ast = Syntax.make_ast_from_file "test/input0.rill" in
  Ast.print ast;
  let (env, ctx) = Sema.make_default_state () in
  let sem_ast = Sema.analyze ast env ctx in
  let module M = (Llvm_codegen : Codegen.GENERATOR_TYPE) in
  let c_ctx = M.generate sem_ast in
  M.create_executable c_ctx "" "a.out"
