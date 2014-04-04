include "album.thrift"

service Store {
    album.Album buyAlbum( 1: string ASIN, 2: string acct ),
    list<album.Album> similar( 1: string ASIN ),
}

