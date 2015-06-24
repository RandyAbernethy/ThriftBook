service SailStats {
   double GetSailorRating(1: string SailorName)
   double GetTeamRating(1: string TeamName)
   double GetBoatRating(1: i64 BoatSerialNumber)
   list<string> GetSailorsOnTeam(1: string TeamName)
   list<string> GetSailorsRatedBetween(1: double MinRating,
                                       2: double MaxRating)
   string GetTeamCaptain(1: string TeamName)
}

