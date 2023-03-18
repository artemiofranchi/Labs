using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace Laboratory_1_Volkov_302
{
    class V4DataCollection: System.Collections.ObjectModel.ObservableCollection<V4Data>
    {
        public new V4Data this[int i]
        {
            get => Items[i];
        }
        public int? IsZeroLINQ
        {
            get
            {
                var request = from v4dataelem in this
                              from item in v4dataelem
                              select item;
                if (request.Count() == 0)
                {
                    return null;
                }
                int count = request.Count(i => ((i.y[0] == 0) || (i.y[1] == 0)));
                if (count == 0)
                {
                    return -1;
                }
                return count;
            }
        }
        public IEnumerable<dataitem> NumRequestLinq
        {
            get
            {
                var request = from v4dataelem in this
                            from item in v4dataelem
                            orderby item.x descending
                            select item;
                if (request.Count() == 0)
                {
                    return null;
                }
                //foreach(dataitem item in request){
                //    Console.WriteLine($"THE ITEM IS {item}");
                //}
                return request;
            }
        }
        public IEnumerable<float> InListNotInNUGrid
        {
            get
            {
                var request1 = from v4dataelem1 in this
                              where (v4dataelem1.GetType() == typeof(V4DataList))
                              from item in v4dataelem1
                              select item.x;
                var request2 = from v4dataelem2 in this
                              where (v4dataelem2.GetType() == typeof(V4DataNUGrid))
                              from item in v4dataelem2
                              select item.x;
                var request = request1.Except(request2).Distinct();
                if (request.Count() == 0)
                {
                    return null;
                }
                return request;
            }
        }
        public bool Contains(string ID)
        {
            for (int i = 0; i < this.Count; i++)
            {
                if (this[i].str == ID)
                {
                    return true;
                }
            }
            return false;
        }
        public bool Remove(string ID)
        {
            if (Contains(ID))
            {
                for (int i = 0; i < this.Count; i++)
                {
                    if (this[i].str == ID)
                    {
                        this.RemoveAt(i);
                    }
                }
                return true;
            }
            return false;
        }
        public new bool Add(V4Data v4data)
        {
            if (!Contains(v4data.str))
            {
                base.Add(v4data);
                return true;
            }
            return false;
        }
        public static float[] F2F(float x)
        {
            float[] myF = { x * x, x + 5.0f };
            return myF;
        }
        public void AddDefaults()
        {
            V4DataList mylist = new V4DataList("Default DataList", new DateTime(2022, 01, 01));
            F2Float myF = F2F;
            mylist.AddDefaults(3, myF);
            Uniformgrid mygrid = new Uniformgrid(1.0f, 3.5f, 3, new DateTime(2022,01,01));
            V4DataUGrid mydugrid = new V4DataUGrid("Default DataUGrid", new DateTime(2022, 01, 01), mygrid, myF);
            float[] mynodes = { 1.3f, 2.3f, 3.1f };
            V4DataNUGrid mydnugrid = new V4DataNUGrid("Default DataNUGrid", new DateTime(2022, 01, 01), mynodes, myF);
            this.Add(mylist);
            this.Add(mydugrid);
            this.Add(mydnugrid);
        }
        public override string ToString()
        {
            string thestr = "";
            for (int i = 0; i < this.Count; i++)
            {
                thestr += this[i].ToString();
            }
            return thestr;
        }
        public string ToLongString(string format)
        {
            string thestr = "";
            for (int i = 0; i < this.Count; i++)
            {
                thestr += this[i].ToLongString(format);
            }
            return thestr;
        }

    }
}
