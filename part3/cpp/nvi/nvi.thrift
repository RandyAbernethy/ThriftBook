struct Trade {
   1: string symbol
   2: double price
   3: i32 size
}

service NVITest {
    i32 report_trade( 1: Trade trade )
}

