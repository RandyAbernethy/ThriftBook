include "track.thrift"			

namespace * music				

struct Album {
    1: list<track.MusicTrack> tracks,	
    2: track.Minutes duration,		
    3: string ASIN
}

