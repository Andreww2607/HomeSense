using Android.App;
using Android.Content;

namespace HomeSense.SpeechToText
{
    public class MicrophoneTester
    {
        private static MicrophoneTester _singleInstance;
        private MicrophoneTester() { }

        public static MicrophoneTester Instance => _singleInstance ?? (_singleInstance = new MicrophoneTester());

        public static bool Test(Context context)
        {
            string rec = Android.Content.PM.PackageManager.FeatureMicrophone;
            if (rec == "android.hardware.microphone") return true;

            //pass context for alert
            var alert = new AlertDialog.Builder(context);
            alert.SetTitle("You don't seem to have a microphone to record with");
            alert.SetPositiveButton("OK", (sender, e) => { });
            alert.Show();
            return false;
        }
    }
}
