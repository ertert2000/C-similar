using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Data.Sqlite;

namespace lib3_1
{
    public static class DatabaseHelper
    {
        public const string ConnectionString = "Data Source=football.db";

        public static void InitializeDatabase()
        {
            var connection = new SqliteConnection(ConnectionString);
            connection.Open();

            var command = connection.CreateCommand();
            command.CommandText = @"
                CREATE TABLE IF NOT EXISTS Players (
                    Id INTEGER PRIMARY KEY AUTOINCREMENT,
                    Name TEXT NOT NULL,
                    FirstName TEXT NOT NULL,
                    Position TEXT NOT NULL,
                    Price INTEGER NOT NULL,
                    MainOrSpare INTEGER NOT NULL
                );

                CREATE TABLE IF NOT EXISTS Games (
                    Id INTEGER PRIMARY KEY AUTOINCREMENT,
                    HomeTeam TEXT NOT NULL,
                    AwayTeam TEXT NOT NULL,
                    GameDate TEXT NOT NULL,
                    IsPlayed INTEGER NOT NULL
                );

                CREATE TABLE IF NOT EXISTS PlayerGames (
                    PlayerId INTEGER NOT NULL,
                    GameId INTEGER NOT NULL,
                    PRIMARY KEY (PlayerId, GameId),
                    FOREIGN KEY (PlayerId) REFERENCES Players(Id),
                    FOREIGN KEY (GameId) REFERENCES Games(Id)
                );
            ";
            command.ExecuteNonQuery();
        }

        public static void AddPlayerToDatabase(FootballPlayers player)
        {
            var connection = new SqliteConnection(ConnectionString);
            connection.Open();

            var command = connection.CreateCommand();
            command.CommandText = @"
            INSERT INTO Players (Name, FirstName, Position, Price, MainOrSpare)
            VALUES (@name, @firstName, @position, @price, @mainOrSpare)";
            command.Parameters.AddWithValue("@name", player.name);
            command.Parameters.AddWithValue("@firstName", player.firstName);
            command.Parameters.AddWithValue("@position", player.position);
            command.Parameters.AddWithValue("@price", player.price);
            command.Parameters.AddWithValue("@mainOrSpare", player.mainOrSpare ? 1 : 0);
            command.ExecuteNonQuery();
        }

        public static void AddGameToDatabase(FootbalGames game)
        {
            var connection = new SqliteConnection(ConnectionString);
            connection.Open();

            var command = connection.CreateCommand();
            command.CommandText = @"INSERT INTO Games (HomeTeam, AwayTeam, GameDate, IsPlayed) 
                            VALUES (@homeTeam, @awayTeam, @gameDate, @isPlayed)";
            command.Parameters.AddWithValue("@homeTeam", game.HomeTeam);
            command.Parameters.AddWithValue("@awayTeam", game.AwayTeam);
            command.Parameters.AddWithValue("@gameDate", game.GameDate.ToString("yyyy-MM-dd"));
            command.Parameters.AddWithValue("@isPlayed", game.IsPlayed ? 1 : 0);
            command.ExecuteNonQuery();
        }


        public static List<FootbalGames> GetGamesForPlayer(int playerId)
        {
            var games = new List<FootbalGames>();

            var connection = new SqliteConnection(ConnectionString);
            connection.Open();

            var command = connection.CreateCommand();
            command.CommandText = @"
        SELECT g.Id, g.HomeTeam, g.AwayTeam, g.GameDate, g.IsPlayed
        FROM Games g
        INNER JOIN PlayerGames pg ON g.Id = pg.GameId
        WHERE pg.PlayerId = @playerId";
            command.Parameters.AddWithValue("@playerId", playerId);

            var reader = command.ExecuteReader();
            while (reader.Read())
            {
                games.Add(new FootbalGames
                {
                    Id = reader.GetInt32(0),
                    HomeTeam = reader.GetString(1),
                    AwayTeam = reader.GetString(2),
                    GameDate = DateTime.Parse(reader.GetString(3)),
                    IsPlayed = reader.GetInt32(4) == 1
                });
            }

            return games;
        }

        public static List<FootbalGames> GetAllGamesFromDatabase()
        {
            var games = new List<FootbalGames>();

            var connection = new SqliteConnection(ConnectionString);
            connection.Open();

            var command = connection.CreateCommand();
            command.CommandText = @"
        SELECT Id, HomeTeam, AwayTeam, GameDate, IsPlayed
        FROM Games";

            var reader = command.ExecuteReader();
            while (reader.Read())
            {
                games.Add(new FootbalGames
                {
                    Id = reader.GetInt32(0),
                    HomeTeam = reader.GetString(1),
                    AwayTeam = reader.GetString(2),
                    GameDate = DateTime.Parse(reader.GetString(3)),
                    IsPlayed = reader.GetInt32(4) == 1
                });
            }

            return games;
        }

    }
}
