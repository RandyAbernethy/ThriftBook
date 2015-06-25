include "radio.thrift"
include "store.thrift"
include "album.thrift"
include "track.thrift"

service RadioContest {
    album.Album RedeemPrize( 1: string callerNumber 
                             2: track.MusicTrack bonusTrack )
}

