using System;
using System.Linq;
using Android.App;
using Android.Content;
using Android.OS;
using Android.Speech;
using Android.Webkit;
using Android.Widget;
using HomeSense.SpeechToText;
using Java.Util;
using System.Threading.Tasks;
using Android.Views;

namespace HomeSense
{
    [Activity(Label = "HomeSense", MainLauncher = true, Icon = "@drawable/iconn", Theme = "@android:style/Theme.Black.NoTitleBar.Fullscreen")]
    public class MainActivity : Activity
    {
        private static readonly int Voice;

        protected override async void OnCreate(Bundle bundle)
        {
            base.OnCreate(bundle);

            // Set our view from the "main" layout resource
            SetContentView(Resource.Layout.Main);

            //spalsh  screen
            var gridView = FindViewById<GridView>(Resource.Id.gridview);
            var splashImage = FindViewById<ImageView>(Resource.Id.splashImageView); 

            //webform view
            var localWebView = FindViewById<WebView>(Resource.Id.LocalWebView);
            localWebView.SetWebViewClient(new WebViewClient());
            localWebView.Settings.JavaScriptEnabled = true;
            localWebView.SetVerticalScrollbarOverlay(true);

            localWebView.LoadUrl("http://192.168.0.2:1880/ui");

            await Task.Delay(7000);

            splashImage.Visibility = ViewStates.Invisible; 
            gridView.Visibility = ViewStates.Invisible;
         

            //speech to text button
            var button = FindViewById<Button>(Resource.Id.MyButton);
            button.Click += delegate
            {
                var speechToTextRecognizer = new Recognizer(ApplicationContext);
                speechToTextRecognizer.Setup();

                var voiceIntent = new Intent(RecognizerIntent.ActionRecognizeSpeech);
                voiceIntent.PutExtra(RecognizerIntent.ExtraLanguageModel, RecognizerIntent.LanguageModelFreeForm);
                //voiceIntent.PutExtra(RecognizerIntent.ExtraPrompt, Application.Context.GetString(Resource.String.messageSpeakNow));
                voiceIntent.PutExtra(RecognizerIntent.ExtraPrompt, "Hello, what can I help you with?");
                voiceIntent.PutExtra(RecognizerIntent.ExtraSpeechInputCompleteSilenceLengthMillis, 1500);
                voiceIntent.PutExtra(RecognizerIntent.ExtraSpeechInputPossiblyCompleteSilenceLengthMillis, 1500);
                voiceIntent.PutExtra(RecognizerIntent.ExtraSpeechInputMinimumLengthMillis, 15000);
                voiceIntent.PutExtra(RecognizerIntent.ExtraMaxResults, 1);
                voiceIntent.PutExtra(RecognizerIntent.ExtraLanguage, Locale.Default);
                StartActivityForResult(voiceIntent, Voice);
            };
        }

        protected override void OnActivityResult(int requestCode, Result resultVal, Intent data)
        {
            if (requestCode == Voice)
            {
                if (resultVal == Result.Ok)
                {
                    var matches = data.GetStringArrayListExtra(RecognizerIntent.ExtraResults);
                    if (!matches.Any())
                    {
                        //ToDo: add text to speech and reply
                        Console.WriteLine("Nothing detected...");
                    }
                    else
                    {
                        var recognizer = new Recognizer(ApplicationContext);
                        recognizer.HandleRecognizedText(matches);
                    }

                }
            }
        }
    }
}

