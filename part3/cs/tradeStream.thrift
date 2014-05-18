/** Apache Thrift IDL definition for the TradeStream service interface */

namespace * PNWF						

enum Market {
    Unknown       = 0
    Portland      = 1
    Seattle       = 2
    SanFrancisco  = 3
    Vancouver     = 4
    Anchorage     = 5
}

typedef double USD

struct TimeStamp {
    1: i16  year
    2: i16  month
    3: i16  day
    4: i16  hour
    5: i16  minute
    6: i16  second
    7: optional i32 micros
} 

union FishSizeUnit {
    1: i32  pounds
    2: i32  kilograms
    3: i16  standard_crates
    4: double  metric_tons
} 

struct Trade {
    1: string       fish                  
    2: USD          price             
    3: FishSizeUnit amount         
    4: TimeStamp    date_time   
    5: Market       market = Market.Unknown
    6: i64          id          
}

/** 
 * Thrown when the server encounters an internal error during 
 * a long polling operation.
 */
exception NetworkError {						
    1: i32          error_code
    2: string       error_message    
    3: set<Market>  markets_with_error
}

service TradeStream {
    /** 
     * Return the next trade report
     *
     * @param fish_filter - fish to return trades for, "" for all
     * @return - the next fish trade occurring 
     * @throws NetworkError - raised when the feed is delayed
     */
    list<Trade> GetNextTrade(1: string fish_filter = "") 		
        throws (1: NetworkError ne)
}

