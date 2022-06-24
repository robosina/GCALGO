## compile the code

```bash
git clone https://github.com/robosina/GCALGO.git
cd GCALGO
mkdir build
cd build 
cmake ..
make
```

You can see that an executable file named `greedy_construction` was created following a successful compilation in the `bin` folder:
```bash
$ cd bin
$ ls
greedy_construction tests
```

We can run the executable file as follows:
```bash
./greedy_construction /path/2/Sample_Input.json
```

We can find a file named `output.json` near the executable if it was successful.
```bash
$ ls
greedy_construction  output.json  tests
```

```bash
$ cat output.json
{
    "planID": "01",
    "trips": [
        {
            "tripId": "T1",
            "vehicleType": "truck",
            "summary": {
                "distanceInMeter": 78178
            },
            "trip": [
                {
                    "pointId": "Start",
                    "lat": 24.937166408801044,
                    "lng": 55.21257733283741,
                    "parentPointId": ""
                },
                {
                    "pointId": "DC2",
                    "lat": 25.119234619804637,
                    "lng": 55.32858343144892,
                    "parentPointId": ""
                },
                {
                    "pointId": "Store14",
                    "lat": 25.16484844479134,
                    "lng": 55.30878207376417,
                    "parentPointId": "DC2"
                },
                .
                .
                .
```
## For first truck(visualized by QML/Qt)
![image](https://user-images.githubusercontent.com/14973524/175574344-02788628-d8cb-487d-b35b-273dafb35efd.png)

## For Second truck(visualized by QML/Qt)
![image](https://user-images.githubusercontent.com/14973524/175574638-6401949a-b725-4255-ba44-1b12584a6ccf.png)
