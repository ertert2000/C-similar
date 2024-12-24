using System;

namespace lib3_1
{
    public class FootbalGames
    {
        public int Id { get; set; }
        public string HomeTeam { get; set; }
        public string AwayTeam { get; set; }
        public DateTime GameDate { get; set; }
        public bool IsPlayed { get; set; }
    }
}
