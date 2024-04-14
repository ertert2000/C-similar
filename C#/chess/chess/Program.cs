using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace chess
{
    public class Board
    {
        public Board()
        {

            int[,] board = new int[8,8];
            for (int i = 0; i < 8; i++) 
                for (int j = 0; j < 8; j++)
                    board[i, j] = 0;

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                    Console.Write(board[i, j] + "\t");
                Console.WriteLine();
            }


        }

        public int getFigure(int[] board)
        {

        }
    }

    public class Pawn
    {

    }


    internal class Program
    {
        static void Main(string[] args)
        {
            Board board = new Board();
        }
    }
}
