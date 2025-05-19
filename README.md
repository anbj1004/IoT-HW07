# IoT25-HW07

## Demo videos:
\<Serial Monitor\>
![Screenshot of Arduino IDE](resources/serial.webp)

\<Video of LED alert (within 1m)\>
![Video of LED alert](resources/led.gif)

\<Photo of real-time distance data on a web server\>
![Screenshot of web server](resources/webserver.jpg)

---
## Test and Analyze

We measured distances at 0.5m, 1m, 2m, 3m, and 4m, and visualized the results using a bar chart. Based on the chart, we adjusted the parameters to obtain values that most closely matched the actual distances. The primary parameter we adjusted was `txPower`. And we set `n = 2`.

Distance estimation model:
	`distance (m) = 10 ^ ((txPower - RSSI) / (10 * n)) (n = 2.0)`

Here is the results:
1. txPower = -70dbm
![Screenshot of bar chart (-70dbm)](resources/bar_plot_70.png)

2. txPower = -66dbm
![Screenshot of bar chart (-66dbm)](resources/bar_plot_66.png)

3. txPower = -59dbm
![Screenshot of bar chart (-59dbm)](resources/bar_plot_59.png)

4. txPower = -55dbm
![Screenshot of bar chart (-55dbm)](resources/bar_plot_55.png)

We concluded from the graph that a `txPower` value of -59 dBm most closely matches the actual distances, and based on this value, we recorded the demonstration video above.