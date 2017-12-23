using System;
using System.Linq;
using System.Windows;

using System.IO.IsolatedStorage;
using System.IO;
using Windows.Storage;
using System.Threading.Tasks;
using System.Diagnostics;

using System.Collections.Generic;

using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Popups;

namespace App1 {
    public sealed  partial class MainPage : Page  {

        bool editando = false;
        String localfolder = Windows.Storage.ApplicationData.Current.LocalFolder.Path;

       

        public  MainPage() {
            this.InitializeComponent();
            String myFileName = String.Concat(localfolder, "\\test.txt");

           


            try
            {
                using (IsolatedStorageFile f = IsolatedStorageFile.GetUserStoreForApplication())
                {
                    //To read
                    using (StreamReader r = new StreamReader(f.OpenFile(myFileName, FileMode.Open)))
                    {
                        string text = r.ReadToEnd();
                        txtBlockAnswer.Text = text;

                    }
                }
            }

            catch (Exception ex) {
                Debug.WriteLine(ex.Message);
            }
                       
        }




        private void btnSubmit_Click(object sender, RoutedEventArgs e) {
            //byte[] resultados = null;

            
			String myFileName = String.Concat(localfolder, "\\test.txt");
           
            int numero;
            numero = Convert.ToInt16(txtBxString.Text);

				// std::wstring stlString = myFileName->Data();

             //CppWINRT.StringCharacterCounter sccMain = new CppWINRT.StringCharacterCounter();

            CppWINRT.clase1 variable1 = new CppWINRT.clase1();
            Double variable2 ;
            variable1.asignar_num(numero, "numerito");
            variable1.asignar_num(5, "numerito2");
            variable1.asignar_num(35, "numerito3");
            String xx = txtBxString.Text;


            variable2 = variable1.run(xx);	// 'ejecuta el programa INTER

            using (IsolatedStorageFile f = IsolatedStorageFile.GetUserStoreForApplication())
            {
                //To read
                using (StreamReader r = new StreamReader(f.OpenFile(myFileName, FileMode.Open )))
                {
                    string text = r.ReadToEnd();
                    txtBlockAnswer.Text = text;

                }
            }



            //txtBlockAnswer.Text = sccMain.GetLength(txtBxString.Text).ToString() + " characters were found in the string above";
            //System.IO.FileStream fs = System.IO.File.OpenRead(myFileName);
            //fs.Read(resultados, 0, 9999);
            //txtBlockAnswer.Text = System.Text.Encoding.UTF8.GetString  (resultados, 0, 9999);
        }

        
        private   async void    btnEdit_Click(object sender, RoutedEventArgs e)
        {
          //   String myFileName2 = String.Concat(localfolder, "\\p1.pr");
          

             if (!editando)
             {
                 txtBlockAnswer.Visibility = Visibility.Collapsed;
                 txtPrograma.Visibility = Visibility.Visible;
                 //txtPrograma.Text = 

                 //using (IsolatedStorageFile f = IsolatedStorageFile.GetUserStoreForApplication())
                 {

                     string  res = await  leer_fichero();

                     //using (StreamReader r = new StreamReader(f.OpenFile(myFileName2, FileMode.Open)))
                     //{
                     //    string text = r.ReadToEnd();
                      txtPrograma.Text = res;

                     //}

                     editando = true;
                 }
             }
             else
             {
                 editando = false;
                 
                 {

                     string res = await escribir_fichero(txtPrograma.Text.ToString());
                     txtBlockAnswer.Text = txtPrograma.Text;
                     txtBlockAnswer.Visibility = Visibility.Visible;
                     txtPrograma.Visibility = Visibility.Collapsed;
                     
                 }

             }
        }

           

        static async Task<string> leer_fichero()
        {
            //var folder = Windows.ApplicationModel.Package.Current.InstalledLocation;
            //var file = await folder.GetFileAsync("sample.txt");
            //  var contents = await Windows.Storage.FileIO.ReadTextAsync(file);

            Windows.Storage.FileAttributes fileAttr;
            //long fileSize = -1;


            FileInfo info = new FileInfo("p1.pr");
            Debug.WriteLine("File size=" + info.Length);
            var dialog = new MessageDialog("file size: " + info.Length);
            await dialog.ShowAsync();

           
            string fileContent;
            StorageFile file = await StorageFile.GetFileFromApplicationUriAsync(new Uri(@"ms-appx:///p1.pr"));
            using (StreamReader sRead = new StreamReader(await file.OpenStreamForReadAsync()))
            {
                fileAttr = file.Attributes;
                

                fileContent = await sRead.ReadToEndAsync();
                //sRead.Close();
                sRead.Dispose();
            }

            return   fileContent  ;
            

        }

        static async Task<string> escribir_fichero(string fileContent)
        {
            //var folder = Windows.ApplicationModel.Package.Current.InstalledLocation;
            //var file = await folder.GetFileAsync("sample.txt");
            //  var contents = await Windows.Storage.FileIO.ReadTextAsync(file);

            try
            {
                StorageFile file = await StorageFile.GetFileFromApplicationUriAsync(new Uri(@"ms-appx:///p1.pr"));
                await file.DeleteAsync();
                //string filename = "p1.pr";
                //IsolatedStorageFile file2 = IsolatedStorageFile.GetUserStoreForApplication();
                //file2.DeleteFile(filename);

                var dialog = new MessageDialog("fichero p1.pr eliminado.");
                await dialog.ShowAsync();

                //MessageBox.Show();

            }

            catch (Exception ex) {

              //  MessageBox.Show("DELETE:" + ex.Message);

            }


            //aqui mal

            try
            {
                 System.Text.Encoding enc = new App1.AsciiEncoding();
                StorageFolder folder = Windows.ApplicationModel.Package.Current.InstalledLocation;

                StorageFile file = await folder.CreateFileAsync("p1.pr", CreationCollisionOption.ReplaceExisting);

                StorageFile file2 = await StorageFile.GetFileFromApplicationUriAsync(new Uri(@"ms-appx:///p1.pr"));
                using (StreamWriter sRead = new StreamWriter(await file2.OpenStreamForWriteAsync() , enc   ))
                {
                    //await sRead.WriteAsync(fileContent);
                    fileContent = fileContent.Replace("\r\n", "\n");
                    fileContent = fileContent.Replace("\r", "\n");
                    sRead.Write(fileContent);
                    //sRead.Close();
                    sRead.Dispose();
                }
            }

            catch (Exception ex) {
              //  MessageBox.Show("WRITE:" + ex.Message);
            }

            try
            {
                FileInfo info = new FileInfo("p1.pr");
                Debug.WriteLine("File size=" + info.Length);
                //MessageBox.Show("file size: " + info.Length);
            }
            catch (Exception ex) {
                //MessageBox.Show("FILESIZE:" + ex.Message);
            }

            return "";

        }


   }



}





            //Dim variable1 As New prueba.clase1		'ver CLASE1 en  main.cpp
            //Dim variable2 As Double


            //variable1.asignar_num(8, "numerito")
            //variable1.asignar_num(5, "numerito2")
            //variable1.asignar_num(35, "numerito3")

            //variable2 = variable1.run(TextBox2.Text.ToString)	'ejecuta el programa INTER

            //TextBox1.Text = System.IO.File.ReadAllText("c:\test.txt ")
            //TextBox1.Text &= vbCrLf
            //TextBox1.Text &= "Valor devuelto: " & Str(variable2) & vbCrLf
            //TextBox1.Text &= "VARIABLE x = " & variable1.buscar_valor("x") & vbCrLf
            //TextBox1.Text &= "VARIABLE y = " & variable1.buscar_valor("y") & vbCrLf
            //TextBox1.Text &= "VARIABLE z = " & variable1.buscar_valor("z") & vbCrLf
            //TextBox1.Text &= "VARIABLE numerito3 = " & variable1.buscar_valor("numerito3") & vbCrLf

/*
string fileContent;
StorageFile file = await StorageFile.GetFileFromApplicationUriAsync(new Uri(@"ms-appx:///example.txt"));
using (StreamReader sRead = new StreamReader(await file.OpenStreamForReadAsync()))
fileContent = await sRead.ReadToEndAsync();
*/
