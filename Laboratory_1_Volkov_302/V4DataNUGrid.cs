using System;
using System.Collections.Generic;
using System.Text;

namespace Laboratory_1_Volkov_302
{
    public class V4DataNUGrid: V4Data
    {
        public float[] node { get; set; }
        public float[] comp1 { get; set; }
        public float[] comp2 { get; set; }

        public V4DataNUGrid(string str, DateTime dt): base(str, dt)
        {
            node = new float[0];
            comp1 = new float[0];
            comp2 = new float[0];
        }
        public V4DataNUGrid(string str, DateTime dt, float[] mynode, F2Float F) : base(str, dt)
        {
            node = mynode;
            comp1 = new float[node.Length];
            comp2 = new float[node.Length];
            for (int i = 0; i < node.Length; i++)
            {
                comp1[i] = F(node[i])[0];
                comp2[i] = F(node[i])[1];
            }
        }
        public override float MaxAbsVal
        {
            get
            {
                float maxval1 = 0;
                float maxval2 = 0;
                for (int i = 0; i < node.Length; i++)
                {
                    maxval1 = Math.Max(maxval1, Math.Abs(comp1[i]));
                    maxval2 = Math.Max(maxval2, Math.Abs(comp2[i]));
                }
                return Math.Max(maxval1, maxval2);
            }
        }
        public override string ToString()
        {
            return $"{System.ComponentModel.TypeDescriptor.GetClassName(this)}, {base.ToString()}";
        }
        public override string ToLongString(string format)
        {
            string res = System.ComponentModel.TypeDescriptor.GetClassName(this)+ " " + base.ToString() + "\n";
            for (int i = 0; i < node.Length; i++)
            {
                res += "x = " + node[i].ToString(format) + ", Values = " + comp1[i].ToString(format)+ "; " + comp2[i].ToString(format) + "\n";
            }
            return res;
        }
        public override IEnumerator<dataitem> GetEnumerator()
        {
            for (int i = 0; i < node.Length; i++)
            {
                yield return new dataitem(node[i], comp1[i], comp2[i]);
            }
        }

    }
}
