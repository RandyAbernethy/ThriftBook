/** Stock Trade Reporting interface */

namespace * TradeReporting

struct TradeReport {
    1: string  symbol,
    2: double  price,
    3: i32     size,
    4: i32     seq_num
} 

service TradeHistory {
    TradeReport GetLastSale(1: string Symbol) 
}

