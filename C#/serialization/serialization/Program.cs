using System;
using System.Collections.Generic;
using System.Linq;
//using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Text.Json;


namespace serialization
{
    public class Person
    {
        public string Name { get; }
        public int Id { get; set; }

        public Person(string name, int id)
        {
            Name = name;
            Id = id;
        }
    }


    public class Ser
    {
        public void WriteDown()
        {
            var per = new Person();

            string odjS = JsonSerializer.Serialize(per);

            File.WriteAllText("DATA.json", odjS);
        }
    }

    internal class Program
    {

        

        static void Main(string[] args)
        {
            var name = Console.ReadLine();
            var age = Console.Read(); 
            Person person = new Person(name, age);

            string json = JsonSerializer.Serialize(person);
            System.Console.WriteLine(json);

            //person.Name = Console.ReadLine();
            //person.Id = Console.Read();

            Ser ser = new Ser();
            ser.WriteDown();

        }
    }
}
