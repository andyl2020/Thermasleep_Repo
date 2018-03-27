/*
    Copyright (c) Xpert360 Ltd All rights reserved.  
 
    MIT License: 
 
    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
    documentation files (the  "Software"), to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
    and to permit persons to whom the Software is furnished to do so, subject to the following conditions: 
 
    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. 
 
    THE SOFTWARE IS PROVIDED ""AS IS"", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
    TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

using System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Microsoft.Band;
using Microsoft.Band.Sensors;
using System.Threading.Tasks;
using Windows.ApplicationModel.Core;
using Windows.UI.Core;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace BandSensors
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        private bool IsRunning = false;

        private async void ButtonRun_Click(object sender, RoutedEventArgs e)
        {
            if (IsRunning)
                return;
            else
                IsRunning = true;

            try
            {
                this.ButtonRun.IsEnabled = false;
                this.StatusMessage.Text = "";

                // Get the list of Microsoft Bands paired to the phone.
                IBandInfo[] pairedBands = await BandClientManager.Instance.GetBandsAsync();
                if (pairedBands.Length < 1)
                {
                    this.StatusMessage.Text = "This sample app requires a Microsoft Band paired to your device. Also make sure that you have the latest firmware installed on your Band, as provided by the latest Microsoft Health app.";
                    return;
                }

                // Connect to Microsoft Band.
                using (IBandClient bandClient = await BandClientManager.Instance.ConnectAsync(pairedBands[0]))
                {
                    if (bandClient.SensorManager.HeartRate.GetCurrentUserConsent() != UserConsent.Granted)
                    {
                        await bandClient.SensorManager.HeartRate.RequestUserConsentAsync();
                    }

                    int samplesReceivedAcc = 0; // the number of Accelerometer samples received
                    int samplesReceivedCal = 0; // the number of Calories samples received
                    int samplesReceivedCon = 0; // the number of Contact samples received
                    int samplesReceivedDist = 0; // the number of Contact samples received
                    int samplesReceivedGyro = 0; // the number of Gyroscope samples received
                    int samplesReceivedHR = 0; // the number of HeartRate samples received
                    int samplesReceivedPed = 0; // the number of Pedometer samples received
                    int samplesReceivedST = 0; // the number of SkinTemperature samples received
                    int samplesReceivedUV = 0; // the number of UV samples received

                    // Subscribe to Accelerometer data.
                    bandClient.SensorManager.Accelerometer.ReadingChanged += (s, args) =>
                    {
                        samplesReceivedAcc++;
                        if ((samplesReceivedAcc % 20) == 0)
                        {
                            // Only report occasional Accelerometer data
                            IBandAccelerometerReading readings = args.SensorReading;
                            CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
                            {
                                this.txtAccelerometer.Text = readings.AccelerationX.ToString() + " " + readings.AccelerationY.ToString() + " " + readings.AccelerationZ.ToString();
                            });
                        }
                    };
                    await bandClient.SensorManager.Accelerometer.StartReadingsAsync();

                    // Subscribe to Calories data.
                    bandClient.SensorManager.Calories.ReadingChanged += (s, args) =>
                    {
                        samplesReceivedCal++;
                        IBandCaloriesReading readings = args.SensorReading;
                        CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
                        {
                            this.txtCalories.Text = readings.Calories.ToString();
                        });
                    };
                    await bandClient.SensorManager.Calories.StartReadingsAsync();

                    // Subscribe to Contact data.
                    bandClient.SensorManager.Contact.ReadingChanged += (s, args) =>
                    {
                        samplesReceivedCon++;
                        IBandContactReading readings = args.SensorReading;
                        CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
                        {
                            this.txtContact.Text = readings.State.ToString();
                        });
                    };
                    await bandClient.SensorManager.Contact.StartReadingsAsync();

                    // Subscribe to Distance data.
                    bandClient.SensorManager.Distance.ReadingChanged += (s, args) =>
                    {
                        samplesReceivedDist++;
                        IBandDistanceReading readings = args.SensorReading;
                        CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
                        {
                            this.txtDistance.Text = readings.CurrentMotion.ToString() + " " + readings.Pace.ToString() + " " + readings.Speed.ToString() + " " + readings.TotalDistance.ToString();
                        });
                    };
                    await bandClient.SensorManager.Distance.StartReadingsAsync();

                    // Subscribe to Gyroscope data.
                    bandClient.SensorManager.Gyroscope.ReadingChanged += (s, args) =>
                    {
                        samplesReceivedGyro++;
                        if ((samplesReceivedGyro % 20) == 0)
                        {
                            // Only report occasional Gyroscope data
                            IBandGyroscopeReading readings = args.SensorReading;
                            CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
                            {
                                this.txtGyroscope.Text = readings.AccelerationX.ToString() + " " + readings.AccelerationY.ToString() + " " + readings.AccelerationX.ToString();
                            });
                        }
                    };
                    await bandClient.SensorManager.Gyroscope.StartReadingsAsync();

                    // Subscribe to HeartRate data.
                    bandClient.SensorManager.HeartRate.ReadingChanged += (s, args) =>
                    {
                        samplesReceivedHR++;
                        IBandHeartRateReading readings = args.SensorReading;
                        CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
                        {
                            this.txtHR.Text = readings.HeartRate.ToString() + " [" + readings.Quality.ToString() + "]";
                        });
                    };
                    await bandClient.SensorManager.HeartRate.StartReadingsAsync();

                    // Subscribe to Pedometer data.
                    bandClient.SensorManager.Pedometer.ReadingChanged += (s, args) =>
                    {
                        samplesReceivedPed++;
                        IBandPedometerReading readings = args.SensorReading;
                        CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
                        {
                            this.txtPedometer.Text = readings.TotalSteps.ToString();
                        });
                    };
                    await bandClient.SensorManager.Pedometer.StartReadingsAsync();

                    // Subscribe to SkinTemperature data.
                    bandClient.SensorManager.SkinTemperature.ReadingChanged += (s, args) =>
                    {
                        samplesReceivedST++;
                        IBandSkinTemperatureReading readings = args.SensorReading;
                        CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () => {
                            this.txtSkinTemp.Text = readings.Temperature.ToString();
                        });
                    };
                    await bandClient.SensorManager.SkinTemperature.StartReadingsAsync();

                    // Subscribe to UV data.
                    bandClient.SensorManager.UV.ReadingChanged += (s, args) =>
                    {
                        samplesReceivedUV++;
                        IBandUVReading readings = args.SensorReading;
                        CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
                        {
                            this.txtUV.Text = readings.IndexLevel.ToString();
                        });
                    };
                    await bandClient.SensorManager.UV.StartReadingsAsync();

                    // Receive sensor data for a while
                    await Task.Delay(TimeSpan.FromSeconds(10));

                    // Stop the sensor subscriptions
                    await bandClient.SensorManager.Accelerometer.StopReadingsAsync();
                    await bandClient.SensorManager.Calories.StopReadingsAsync();
                    await bandClient.SensorManager.Contact.StopReadingsAsync();
                    await bandClient.SensorManager.Distance.StopReadingsAsync();
                    await bandClient.SensorManager.Gyroscope.StopReadingsAsync();
                    await bandClient.SensorManager.HeartRate.StopReadingsAsync();
                    await bandClient.SensorManager.Pedometer.StopReadingsAsync();
                    await bandClient.SensorManager.SkinTemperature.StopReadingsAsync();
                    await bandClient.SensorManager.UV.StopReadingsAsync();

                    this.StatusMessage.Text = string.Format("Done.\n {0} Accelerometer samples received.\n {1} Calories samples received.\n {2} Contact samples received.\n {3} Distance samples received.\n {4} Gyroscope samples received.\n {5} HeartRate samples received.\n {6} Pedometer samples received.\n {7} SkinTemperature samples received.\n {8} UV samples received.", samplesReceivedAcc, samplesReceivedCal, samplesReceivedCon, samplesReceivedDist, samplesReceivedGyro, samplesReceivedHR, samplesReceivedPed, samplesReceivedST, samplesReceivedUV);
                }
            }
            catch (Exception ex)
            {
                this.StatusMessage.Text = ex.ToString();
            }
            IsRunning = false;
            this.ButtonRun.IsEnabled = true;
        }
    }
}
