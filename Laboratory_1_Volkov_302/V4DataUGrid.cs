using System;
using System.Collections.Generic;
using System.IO;
using System.Text;


namespace Laboratory_1_Volkov_302
{
    public class V4DataUGrid: V4Data
    {
        public Uniformgrid grid { get; set; }
        public float[] arr1 { get; set; }
        public float[] arr2 { get; set; }
        public V4DataUGrid(string str, DateTime dt) : base(str, dt)
        {
            arr1 = new float[0];
            arr2 = new float[0];
        }
        public V4DataUGrid(string str, DateTime dt, Uniformgrid mygrid, F2Float F) : base(str, dt)
        {
            grid = mygrid;
            arr1 = new float[grid.nodes];
            arr2 = new float[grid.nodes];
            for (int i = 0; i < grid.nodes; i++)
            {
                arr1[i] = F(grid.leftend + i*grid.h)[0];
                arr2[i] = F(grid.leftend + i*grid.h)[1];
            }
        }
        public override float MaxAbsVal
        {
            get
            {
                float maxval1 = 0;
                float maxval2 = 0;
                for (int i = 0; i<grid.nodes; i++)
                {
                    maxval1 = Math.Max(maxval1, Math.Abs(arr1[i]));
                    maxval2 = Math.Max(maxval2, Math.Abs(arr2[i]));
                }
                return Math.Max(maxval1, maxval2);
            }
        }
        public static explicit operator V4DataNUGrid(V4DataUGrid source)
        {
            V4DataNUGrid result = new V4DataNUGrid(source.str, source.dt);
            result.node = new float[source.grid.nodes];
            result.comp1 = new float[source.grid.nodes];
            result.comp2 = new float[source.grid.nodes];
            for (int i = 0; i < source.grid.nodes; i++)
            {
                result.node[i] = source.grid.leftend + i * source.grid.h;
                result.comp1[i] = source.arr1[i];
                result.comp2[i] = source.arr2[i];
            }
            return result;

        }
        public override string ToString()
        {
            return $"{System.ComponentModel.TypeDescriptor.GetClassName(this)},  {base.ToString()}, Grid parameters = {grid.leftend}; {grid.rightend}\n";
        }
        public override string ToLongString(string format)
        {
            string res = System.ComponentModel.TypeDescriptor.GetClassName(this) + " " + base.ToString() + "Grid parameters = " + grid.leftend +"; " + grid.rightend + "\n";
            for (int i = 0; i<grid.nodes; i++)
            {
                float step = grid.leftend + i * grid.h;
                res += "x = " + step.ToString(format) + ", Values = " + arr1[i].ToString(format) + "; " + arr2[i].ToString(format) + "\n";
            }
            
            return res;
        }
        public override IEnumerator<dataitem> GetEnumerator()
        {
            for (int i = 0; i < grid.nodes; i++)
            {
                yield return new dataitem(grid.leftend + i * grid.h, arr1[i], arr2[i]);
            }
        }
        public bool Save(string filename)
        {
            FileStream fs = null;
            try
            {
                fs = new FileStream(filename, FileMode.OpenOrCreate);
                BinaryWriter writer = new BinaryWriter(fs);
                writer.Write(str);
                writer.Write(dt.Year);
                writer.Write(dt.Month);
                writer.Write(dt.Day);
                writer.Write(dt.Hour);
                writer.Write(dt.Minute);
                writer.Write(dt.Second);
                writer.Write(MaxAbsVal);
                writer.Write(grid.leftend);
                writer.Write(grid.rightend);
                writer.Write(grid.nodes);
                for (int i = 0; i < grid.nodes; i++)
                {
                    writer.Write(arr1[i]);
                    writer.Write(arr2[i]);
                }
                writer.Close();
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return false;
            }
            finally
            {
                if (fs != null)
                {
                    fs.Close();
                }
            }
        }
        public static bool Load(string filename, ref V4DataUGrid V4)
        {
            FileStream fs = null;
            try
            {
                fs = new FileStream(filename, FileMode.Open);
                BinaryReader binaryReader = new BinaryReader(fs);
                V4.str = binaryReader.ReadString();
                V4.dt = new DateTime(binaryReader.ReadInt32(),
                                    binaryReader.ReadInt32(),
                                    binaryReader.ReadInt32(),
                                    binaryReader.ReadInt32(),
                                    binaryReader.ReadInt32(),
                                    binaryReader.ReadInt32());
                V4.MaxAbsVal = binaryReader.ReadSingle();
                V4.grid = new Uniformgrid(binaryReader.ReadSingle(),
                    binaryReader.ReadSingle(),
                    binaryReader.ReadInt32(), V4.dt);

                V4.arr1 = new float[V4.grid.nodes];
                V4.arr2 = new float[V4.grid.nodes];
                for (int i = 0; i < V4.grid.nodes; i++)
                {
                    V4.arr1[i] = binaryReader.ReadSingle();
                    V4.arr2[i] = binaryReader.ReadSingle();

                }


                binaryReader.Close();

                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return false;
            }
            finally
            {
                if (fs != null)
                {
                    fs.Close();
                }
            }
        }
    }
}
