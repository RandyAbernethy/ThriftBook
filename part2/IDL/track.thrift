namespace * music		

enum PerfRightsOrg {	
    ASCAP = 1
    BMI = 2
    SESAC = 3
    Other = 4
}

typedef double Minutes	

/** Music tracks

*/
struct MusicTrack {		
    1: string title
    /** comment 2 */
    2: string artist
    3: string publisher   /* coment 1 */
    4: string composer
    5: Minutes duration
    6: PerfRightsOrg pro
}

