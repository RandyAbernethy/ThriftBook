include "track.thrift"

service Radio {
    list<track.MusicTrack> getPlayList( 1: i16 hour ),
    void makeRequest( 1: track.MusicTrack track ),
}

