struct tree {
   1: tree &left
   2: tree &right
}

service simple {
   void hello(1: string msg, 2: tree t)
}
