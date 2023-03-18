using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace Laboratory_1_Volkov_302
{
    public abstract class V4Data: IEnumerable<dataitem>
    {
        List<dataitem> DataList = null;
        public string str { get; set; }
        public DateTime dt { get; set; }
        public V4Data(string str, DateTime dt)
        {
            this.str = str;
            this.dt = dt;
        }
        virtual public float MaxAbsVal { get; set; }
        public abstract string ToLongString(string format);
        public override string ToString()
        {
            return $"string = {str}, Date = {dt} ";
        }

        public abstract IEnumerator<dataitem> GetEnumerator();

        IEnumerator IEnumerable.GetEnumerator()
        {
            return DataList.GetEnumerator();
        }
    }

}
