using System;
using System.Collections.Generic;
namespace Laboratory_1_Volkov_302
{
    class Program
    {
        static void Main(string[] args)
        {
            //1
            //Console.WriteLine("---Task 1---\n");
            //Console.WriteLine("DataUGrid to DataNUGrid\n");
            dataitem di = new dataitem(1, 2.3f, 3.13545678900f);
            Uniformgrid grid = new Uniformgrid(1.5f, 2.4f, 4, DateTime.Now);
            V4DataUGrid mydugrid = new V4DataUGrid("My DataUGrid ", DateTime.UtcNow, grid, F2F);
            //Console.WriteLine(mydugrid.ToLongString("f2"));
            V4DataNUGrid mydnugrid = (V4DataNUGrid)mydugrid;
            //Console.WriteLine(mydnugrid.ToLongString("f2"));
            //Console.WriteLine("----------------------\n");

            ////2
            //Console.WriteLine("---Task 2---\n");
            //Console.WriteLine("DataCollection\n");
            V4DataCollection mycollection = new V4DataCollection();
            mycollection.AddDefaults();
            //Console.WriteLine(mycollection.ToLongString("f2"));
            //Console.WriteLine("----------------------\n");

            ////3
            //Console.WriteLine("---Task 3---\n");
            //Console.WriteLine("MaxAbsValue\n");
            //for (int i = 0; i < mycollection.Count; i++)
            //{
            //    Console.WriteLine(mycollection[i].MaxAbsVal);
            //}
            //Console.WriteLine("----------------------\n");

            //4
            Console.WriteLine("---Laboratory_2---\n");
            Console.WriteLine("----------------------\n");
            CollectionLINQ(mycollection);
            Console.WriteLine("\n----------------------\n");
            DateTime dt = new DateTime(2022, 12, 12);
            //Console.WriteLine("Original:\n");
            //Console.WriteLine(mydugrid.ToLongString("f2"));
            //V4DataUGrid Copy_dugrid = new V4DataUGrid("new UGrid", new DateTime(2022,1,1));
            ////Save_and_Load(mydugrid, Copy_dugrid, "myfile.txt");
            //Console.WriteLine("Loaded:");
            //Console.WriteLine(Copy_dugrid.ToLongString("f2"));
            //Console.WriteLine("\n");

        }
        public static float[] F2F(float x)
        {
            float[] myF = { x*x, x + 5.0f };
            return myF;
        }
        static void Save_and_Load(V4DataUGrid original, V4DataUGrid loaded, string path)
        {
            bool saved = original.Save(path);
            if (saved)
            {
                bool load = V4DataUGrid.Load(path, ref loaded);
                if (!load)
                {
                    Console.WriteLine("Loading failed!");
                }
            }
            else
            {
                Console.WriteLine("Saving failed!");
            }
        }
        static void CollectionLINQ(V4DataCollection collection)
        {
            collection.Add(new V4DataList("Empty List", DateTime.Now));
            collection.Add(new V4DataUGrid("Empty UGrid", DateTime.Now));
            collection.Add(new V4DataNUGrid("Empty NUGrid", DateTime.Now));
            Console.WriteLine(collection.ToLongString("f2"));
            Console.WriteLine($"ZeroLinq check: {collection.IsZeroLINQ}\n");
            Console.WriteLine("----------------------\n");
            Console.WriteLine("NumRequestLinq:");
            foreach (dataitem item in collection.NumRequestLinq)
            {
                Console.WriteLine($"{item}");
            }
            Console.WriteLine("\n----------------------\n");
            Console.WriteLine("InListNotInNUGrid");
            foreach (float i in collection.InListNotInNUGrid)
            {
                Console.WriteLine($"{i}");
            }
        }
    }
}
