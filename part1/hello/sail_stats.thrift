service SailStats {
    double get_sailor_rating(1: string sailor_name)
    double get_team_rating(1: string team_name)
    double get_boat_rating(1: i64 boat_serial_number)
    list<string> get_sailors_on_team(1: string team_name)
    list<string> get_sailors_rated_between(1: double min_rating,
                                           2: double max_rating)
    string get_team_captain(1: string team_name)
}
