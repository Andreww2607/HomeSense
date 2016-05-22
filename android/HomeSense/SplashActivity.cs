using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using System.Threading.Tasks;

namespace HomeSense
{
    [Activity(Label = "Evolve",  NoHistory = true, Theme = "@style/Theme.Splash")]
    public class SplashScreen : Activity
    {
        protected override async void OnCreate(Bundle bundle)
        {
            base.OnCreate(bundle);
            SetContentView(Resource.Layout.Splash);

        }
    }
}