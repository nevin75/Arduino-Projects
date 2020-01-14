// Lesson 12 - Assignment
// Author - Mike Orsega
using System;
using System.IO;
using System.Reflection.Emit
using System.Windows.Controls;

public class MovieGUI : Form
{
    private Label lblHeading;
    private Label lblData;
    private Label lblName;
    private Label lblRating;
    private TextBox txtName;
    private TextBox txtRating;
    private Button btnAddData;
    private Button btnQuit;
    private Button btnAdd;
    private Button btnDisplay;

    private String[] name = new String[20];
    private int[] rating = new int[20];
    private int numOfMovies = 0;

    private Boolean toggle = false;


    public static void Main()
    {
        MovieGUI m = new MovieGUI();
        m.readData();
        Application.Run(m);
    }

    public MovieGUI()
    {
        Text = "My Movie Rating System";
        Width = 300;
        Height = 400;
        BackColor = Color.Blue;
        ForeColor = Color.White;

        // Data Label
        lblData = new Label();
        lblData.BackColor = Color.White;
        lblData.ForeColor = Color.Black;
        lblData.Top = 10;
        lblData.Left = 10;
        lblData.Width = 275;
        lblData.Height = 300;
        Controls.Add(lblData);

        // Heading Label
        lblHeading = new Label();
        lblHeading.Top = 20;
        lblHeading.Left = 100;
        lblHeading.Width = 102;
        lblHeading.Text = "New Movie Data";
        lblHeading.Visible = false;
        Controls.Add(lblHeading);


        // Name Prompt Label
        lblName = new Label();
        lblName.Top = 50;
        lblName.Left = 40;
        lblName.Width = 102;
        lblName.Text = "Enter Movie Name:";
        lblName.Visible = false;
        Controls.Add(lblName);

        // Name TextBox
        txtName = new TextBox();
        txtName.Top = 50;
        txtName.Left = 148;
        txtName.Text = "";
        txtName.Visible = false;
        Controls.Add(txtName);

        // Rating Prompt Label
        lblRating = new Label();
        lblRating.Top = 90;
        lblRating.Left = 40;
        lblRating.Width = 108;
        lblRating.Text = "Enter Movie Rating:";
        lblRating.Visible = false;
        Controls.Add(lblRating);

        // Rating TextBox
        txtRating = new TextBox();
        txtRating.Top = 90;
        txtRating.Left = 148;
        txtRating.Text = "";
        txtRating.Visible = false;
        Controls.Add(txtRating);

        // AddData Button
        btnAddData = new Button();
        btnAddData.Left = 110;
        btnAddData.Top = 130;
        btnAddData.Text = "Add Data";
        btnAddData.BackColor = Color.White;
        btnAddData.ForeColor = Color.Black;
        btnAddData.Click += new System.EventHandler(btnAddData_Click);
        btnAddData.Visible = false;
        Controls.Add(btnAddData);

        // Quit Button
        btnQuit = new Button();
        btnQuit.Left = 10;
        btnQuit.Top = 325;
        btnQuit.Text = "Quit";
        btnQuit.BackColor = Color.White;
        btnQuit.ForeColor = Color.Black;
        btnQuit.Click += new System.EventHandler(btnQuit_Click);
        Controls.Add(btnQuit);

        // Add Button
        btnAdd = new Button();
        btnAdd.Left = 110;
        btnAdd.Top = 325;
        btnAdd.Text = "Add";
        btnAdd.BackColor = Color.White;
        btnAdd.ForeColor = Color.Black;
        btnAdd.Click += new System.EventHandler(btnAdd_Click);
        Controls.Add(btnAdd);

        // Display Button
        btnDisplay = new Button();
        btnDisplay.Left = 210;
        btnDisplay.Top = 325;
        btnDisplay.Text = "Display";
        btnDisplay.BackColor = Color.White;
        btnDisplay.ForeColor = Color.Black;
        btnDisplay.Click += new System.EventHandler(btnDisplay_Click);
        Controls.Add(btnDisplay);
    }

    private void btnQuit_Click(object sender, System.EventArgs e)
    {
        quit();
        this.Close();
    }

    private void btnAdd_Click(object sender, System.EventArgs e)
    {
        toggleControls();
    }

    private void btnDisplay_Click(object sender, System.EventArgs e)
    {
        display(name, rating, numOfMovies);
    }

    private void btnAddData_Click(object sender, System.EventArgs e)
    {
        String strRating;

        strRating = txtRating.Text;
        try
        {
            rating[numOfMovies] = Convert.ToInt32(txtRating.Text);
        }
        catch (FormatException)
        {
            MessageBox.Show("Rating must be a whole number!");
            return;
        }

        name[numOfMovies] = txtName.Text;
        numOfMovies++;

        txtName.Text = "";
        txtRating.Text = "";

        toggleControls();
        lblData.Text = "";
    }

    private void toggleControls()
    {
        lblData.Visible = toggle;
        btnAdd.Visible = toggle;
        btnDisplay.Visible = toggle;
        btnQuit.Visible = toggle;

        if (toggle)
            toggle = false;
        else
            toggle = true;

        lblHeading.Visible = toggle;
        lblName.Visible = toggle;
        txtName.Visible = toggle;
        lblRating.Visible = toggle;
        txtRating.Visible = toggle;
        btnAddData.Visible = toggle;
    }

    public void readData()
    {
        String strNum, strRating;
        int i;

        try
        {
            StreamReader inFile = File.OpenText("movieData.txt");
            strNum = inFile.ReadLine();
            try
            {
                numOfMovies = Convert.ToInt32(strNum);
            }
            catch (FormatException)
            {
                Console.Out.WriteLine("\n\nCOULD NOT READ DATA FILE!");
                numOfMovies = 0;
            }

            for (i = 0; i < numOfMovies; i++)
            {
                name[i] = inFile.ReadLine();
                strRating = inFile.ReadLine();
                try
                {
                    rating[i] = Convert.ToInt32(strRating);
                }
                catch (FormatException)
                {
                    Console.Out.Write("\nInvalid Rating Format for " + name[i]);
                    Console.Out.WriteLine(", using 0");
                    rating[i] = 0;
                }
            }

            inFile.Close();
        }
        catch (FileNotFoundException)
        {
            numOfMovies = 0;
            return;
        }
    }

    public void display(string[] _name, int[] _rating, int _num)
    {
        int i;

        lblData.Text = "Current Movie Data";
        lblData.Text += "\n***********************";

        for (i = 0; i < _num; i++)
            lblData.Text += "\n" + _name[i] + " with " + _rating[i] + " stars.";

    }

    public void quit()
    {
        int i;

        StreamWriter outFile = File.CreateText("movieData.txt");
        outFile.WriteLine(numOfMovies);

        for (i = 0; i < numOfMovies; i++)
        {
            outFile.WriteLine(name[i]);
            outFile.WriteLine(rating[i]);
        }

        outFile.Close();

        MessageBox.Show("Your Data was saved!");
    }
}