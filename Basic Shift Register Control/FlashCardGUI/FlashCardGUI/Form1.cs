using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FlashCardGUI
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            Height = 500;
            Width = 300;
            Text = "Hello World";
         
            BackColor = Color.LightGreen;
            ForeColor = Color.LightGreen;
            Button button;
            button.BackColor = Color.AliceBlue;

        }
    }
}
