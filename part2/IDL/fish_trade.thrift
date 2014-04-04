/** Apache Thrift IDL definition for the TradeHistory service interface */

namespace * FishTrade

enum Market {
    Unknown       = 0,
    Portland      = 1,
    Seattle       = 2,
    SanFrancisco  = 3,
    Vancouver     = 4,
    Anchorage     = 5,
}

typedef double USD

struct TimeStamp {
    1: i16  year,
    2: i16  month,
    3: i16  day,
    4: i16  hour,
    5: i16  minute,
    6: i16  second,
    7: optional i32 micros,
} 

union FishSizeUnit {
    1: i32  pounds,
    2: i32  kilograms,
    3: i16  standard_crates,
    4: double  metric_tons,
} 

struct Trade {
    1: string       fish,                 //The symbol for the fish traded
    2: USD          price,                //Price per size unit in USD
    3: FishSizeUnit amount,               //Amount traded
    4: TimeStamp    date_time,            //Date/time trade occured
    5: Market       market=Market.Unknown,//Market where trade occured
} 

exception BadFish {
    1: string       fish,       //The problem fish
    2: i16          error_code, //The service specific error code
}

exception BadFishes {
    1: map<string, i16>  fish_errors, //The problem fish:error pairs
}

service TradeHistory {
    /** 
     * Return most recent trade report for fish type
     *
     * @param fish the symbol for the fish traded
     * @return the most recent trade report for the fish 
     * @throws BadFish if fish has no trade history or is invalid
     */
    Trade GetLastSale(1: string fish) 
        throws (1: BadFish bf),

    /** 
     * Return most recent trade report for multiple fish types
     *
     * @param fish the symbols for the fish to return trades for
     * @param fail_fast if set true the first invalid fish symbol is thrown
     *                  as a BadFish exception, if set false all of the bad 
     *                  fish symbols are thrown using the BadFishes 
     *                  exception.
     * @return list of trades cooresponding to the fish supplied, the list
     *         returned need not be in the same order as the input list
     * @throws BadFish first fish discovered to be invalid or without a 
     *                 trade history (only occurs if skip_bad_fish=false)
     */
    list<Trade> GetLastSaleList(1: set<string> fish, 
                                2: bool fail_fast=false) 
        throws (1: BadFish bf, 2: BadFishes bfs),
}

