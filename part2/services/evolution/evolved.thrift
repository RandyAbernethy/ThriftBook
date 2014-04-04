service SocialLookup {
    string GetSiteByRank( 1: i32 rank );
    i32 GetSiteRankByName(1: string name, 2: bool allowPartialMatch=false);
    list<string> GetSitesByUsers(1: i32 minUserCount, 2: i32 maxUserCount);
}

