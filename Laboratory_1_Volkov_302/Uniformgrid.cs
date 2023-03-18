using System;
using System.Collections.Generic;
using System.Text;

namespace Laboratory_1_Volkov_302
{
    public struct Uniformgrid
    {
        public float leftend { get; set;}
        public float rightend { get; set;}
        public int nodes { get; set; }
        private DateTime dt;
        public DateTime DateTime
        {
            get { return dt; }
            set { dt = value; }
        }

        public float h { get { return (rightend - leftend) / nodes ; } }
        public Uniformgrid(float leftend, float rightend, int nodes, DateTime dt)
        {
            this.dt = dt;
            this.leftend = leftend;
            this.rightend = rightend;
            this.nodes = nodes;

        }
        public override string ToString()
        {
            return $"leftend = {leftend}, rightend = {rightend}, Datetime = {dt}";
        }

    }
}
