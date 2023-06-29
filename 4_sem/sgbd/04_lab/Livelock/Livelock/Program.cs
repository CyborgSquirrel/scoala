using System;
using System.Data.SqlClient;
using System.Threading;

namespace Livelock
{
    class Program
    {
        static string connectionString = @"Server=127.0.0.1;Database=Biblioteca;User Id=sa;Password=top_secret1000;TrustServerCertificate=true;";

        private static volatile bool thread1Success = false;
        private static volatile bool thread2Success = false;

        private static int thread1Attempts = 5;
        private static int thread2Attempts = 5;

        private static AutoResetEvent resetEvent = new AutoResetEvent(false);

        static void Main(string[] args)
        {
            Thread thread1 = null;
            Thread thread2 = null;
            
            while (true)
            {
                if (thread1 != null)
                {
                    if ((thread1.ThreadState & ThreadState.Running) == 0)
                    {
                        thread1 = null;
                    }
                }

                if (thread1 == null && !thread1Success && thread1Attempts > 0)
                {
                    Console.WriteLine("Starting Thread1");
                    
                    thread1Attempts -= 1;
                    thread1 = new Thread(Thread1);
                    thread1.Start();
                }
                
                if (thread2 != null)
                {
                    if ((thread2.ThreadState & ThreadState.Running) == 0)
                    {
                        thread2 = null;
                    }
                }

                if (thread2 == null && !thread2Success && thread2Attempts > 0)
                {
                    Console.WriteLine("Starting Thread2");
                    
                    thread2Attempts -= 1;
                    thread2 = new Thread(Thread2);
                    thread2.Start();
                }

                if (thread1Success && thread2Success)
                {
                    break;
                }

                if (thread1Attempts <= 0 && thread2Attempts <= 0)
                {
                    break;
                }

                resetEvent.WaitOne();
            }
        }

        static void Thread1()
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();
                    string commandText = @"
                        BEGIN TRAN;
                            UPDATE Carte
                            SET titlu = '1 hehehe ha'
                            WHERE id = 53192;
                            WAITFOR DELAY '00:00:07';
                            UPDATE Carte
                            SET titlu = '2 hehehe ha'
                            WHERE id = 53195;
                        ROLLBACK TRAN;
                    ";
                    SqlCommand command = new SqlCommand(commandText, connection);
                    command.ExecuteNonQuery();
                }

                thread1Success = true;
            }
            catch (Exception e)
            {
                Console.WriteLine($"Thread 1 blew up: {e}");
            }

            resetEvent.Set();
        }

        static void Thread2()
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();
                    string commandText = @"
                        BEGIN TRAN;
                            UPDATE Biblioteca.dbo.Carte
                            SET titlu = '3 hehehe ha'
                            WHERE id = 53195;
                            WAITFOR DELAY '00:00:07';
                            UPDATE Biblioteca.dbo.Carte
                            SET titlu = '4 hehehe ha'
                            WHERE id = 53192;
                        ROLLBACK TRAN;
                    ";
                    SqlCommand command = new SqlCommand(commandText, connection);
                    command.ExecuteNonQuery();
                }
                thread2Success = true;
            }
            catch (Exception e)
            {
                Console.WriteLine($"Thread 2 blew up: {e}");
            }
            
            resetEvent.Set();
        }
    }
}