using System;
using System.Collections.Generic;
using System.Text;

namespace Laboratory_1_Volkov_302
{
    class V4DataList: V4Data
    {
        public List<dataitem> DataList
        {
            get;
        }
        public V4DataList(string str, DateTime dt): base(str,dt)
        {
            DataList = new List<dataitem>();
        }
        public bool Add(float x, float v1, float v2)
        {
            dataitem newelem = new dataitem(x, v1, v2);
            if (DataList.TrueForAll(i => i.x != newelem.x)){
                DataList.Add(newelem);
                return true;
            }
            return false;
        }
        public void AddDefaults(int nItems, F2Float F)
        {
            for (int i = 0; i < nItems; i++)
            {
               // Random random = new Random();
                float x = (i+1)*(1.3f);
                Add(x,F(x)[0],F(x)[1]);
            }
        }
        public override float MaxAbsVal
        {   
            get
            {
                float m = 0;
                for (int i = 0; i < DataList.Count; i++)
                {

                    float t1 = DataList[i].y[0];
                    float t2 = DataList[i].y[1];
                    float t = Math.Max(Math.Abs(t1), Math.Abs(t2));
                    if (t > m){
                        m = t;
                    }
                }
                return m;
            }
        }

        public override string ToString()
        {
            return $"{System.ComponentModel.TypeDescriptor.GetClassName(this)} {base.ToString()}  List Length = {DataList.Count.ToString()}";
        }
        public override string ToLongString(string format)
        {
            string res = System.ComponentModel.TypeDescriptor.GetClassName(this) + " " + base.ToString() + " List Length = " + DataList.Count.ToString() + "\n";
            for (int i = 0; i < DataList.Count; i++)
            {
                res += "x = " + DataList[i].x + " y = " + DataList[i].y[0] + " " + DataList[i].y[1] + "\n";
            }
            return res;
        }
        public override IEnumerator<dataitem> GetEnumerator()
        {
            return DataList.GetEnumerator();
        }
    }
}
