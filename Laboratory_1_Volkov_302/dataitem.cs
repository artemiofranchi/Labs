using System;
using System.Collections.Generic;
using System.Text;

namespace Laboratory_1_Volkov_302
{
    public delegate float[] F2Float(float x);
    public struct dataitem
    {
        public float x { get; set; }
        public float[] y { get; set; }
        public dataitem(float x, float y1, float y2)
        {
            this.x = x;
            y = new float[2];
            y[0] = y1;
            y[1] = y2;
        }
        public string ToLongString(string format)
        {
            return $"x = {x.ToString(format)}, y = {y[0].ToString(format)} {y[1].ToString(format)}";
        }
        public override string ToString()
        {
            return $"x = {x}, y1 = {y[0]}, y2 = {y[1]}";
        }
    }

}
