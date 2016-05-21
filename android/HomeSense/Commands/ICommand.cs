using System;
using System.Collections.Generic;
using System.IO;
using System.Net;

namespace HomeSense.Commands
{
    public interface ICommand
    {
        List<string> Parameters { get; set; }
        void Send();
    }

    public class TemperatureCommand : ICommand
    {
        public List<string> Parameters { get; set; }

        public void Send()
        {
            var request = WebRequest.Create("http://192.168.0.2:1880/test");
            request.ContentType = "application/json";
            request.Method = "GET";

            using (var response = request.GetResponse() as HttpWebResponse)
            {
                if (response == null) return;

                if (response.StatusCode != HttpStatusCode.OK)
                    Console.WriteLine("Error fetching data. Server returned status code: {0}", response.StatusCode);
                using (var reader = new StreamReader(response.GetResponseStream()))
                {
                    var content = reader.ReadToEnd();
                    if (string.IsNullOrWhiteSpace(content))
                    {
                        Console.WriteLine("Response contained empty body...");
                    }
                    else
                    {
                        Console.WriteLine("Response Body: \r\n {0}", content);
                    }
                }
            }
        }
    }

}