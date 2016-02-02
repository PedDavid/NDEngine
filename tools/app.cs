using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace tools {
    public partial class app : Form {
        public app() {
            InitializeComponent();
        }

        private void app_Load(object sender, EventArgs e) {

        }

        private void richTextBox1_TextChanged(object sender, EventArgs e) {

        }

        private void button1_Click(object sender, EventArgs e) {

        }

        private void saveHasToolStripMenuItem_Click(object sender, EventArgs e) {

        }

        private void fileToolStripMenuItem_Click(object sender, EventArgs e) {
            
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e) {
            
        }

        SaveFileDialog defaultSave;

        private void openToolStripMenuItem_Click(object sender, EventArgs e) {
            System.IO.Stream myStream = null;
            OpenFileDialog openFileDialog1 = new OpenFileDialog();

            openFileDialog1.InitialDirectory = "c:\\";
            openFileDialog1.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
            openFileDialog1.FilterIndex = 2;
            openFileDialog1.RestoreDirectory = true;

            if (openFileDialog1.ShowDialog() == DialogResult.OK) {
                try {
                    if ((myStream = openFileDialog1.OpenFile()) != null) {
                        byte[] bytes = new byte[myStream.Length];
                        myStream.Position = 0;
                        myStream.Read(bytes, 0, (int)myStream.Length);
                        string data = Encoding.ASCII.GetString(bytes);
                        richTextBox1.AppendText(data);

                        defaultSave = new SaveFileDialog();
                        defaultSave.FileName = openFileDialog1.FileName;
                    }
                } catch (Exception ex) {
                    MessageBox.Show("Error: Could not read file from disk. Original error: " + ex.Message);
                }
            }
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e) {
            if(defaultSave != null) {
                richTextBox1.SaveFile(defaultSave.FileName, RichTextBoxStreamType.PlainText);
                return;
            }
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.DefaultExt = "*.txt";
            sfd.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
            if(sfd.ShowDialog() == DialogResult.OK && sfd.FileName.Length > 0) {
                richTextBox1.SaveFile(sfd.FileName, RichTextBoxStreamType.PlainText);
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e) {
            this.Close();
        }
    }
}
