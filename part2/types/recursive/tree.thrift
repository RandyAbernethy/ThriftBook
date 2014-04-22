struct tree {
   1: tree left (cpp.ref="")
   2: tree right (cpp.ref="")
}

service simple {
   void hello(1: string msg, 2: tree t)
}
