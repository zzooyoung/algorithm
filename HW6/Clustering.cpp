#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

// 구조체로 2D 점을 정의
struct Point {
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    // 두 점 간의 유클리드 거리 계산
    double distance(const Point& p) const {
        return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
    }

    bool operator<(const Point& p) const {
        return x == p.x ? y < p.y : x < p.x;
    }
};

// Approximate K-Clustering 알고리즘 수행
void approximateKClustering(vector<Point>& points, int k, vector<Point>& centers, vector<vector<Point>>& clusters) {
    int n = points.size();
    clusters.assign(k, vector<Point>());

    // 첫 번째 센터는 첫 번째 점으로 설정
    centers.push_back(points[0]);

    // 두 번째 센터는 첫 번째 센터로부터 가장 먼 점을 선택
    double maxDist = -1;
    int maxIndex = -1;
    for (int i = 1; i < n; ++i) {
        double dist = points[i].distance(centers[0]);
        if (dist > maxDist) {
            maxDist = dist;
            maxIndex = i;
        }
    }
    centers.push_back(points[maxIndex]);  // 두 번째 센터는 첫 번째 센터로부터 가장 먼 점

    // 세 번째 센터부터는 기존 센터들과의 거리 중 가장 작은 값이 최대인 점을 선택
    for (int i = 2; i < k; ++i) {
        double maxMinDist = -1;
        int maxMinDistIndex = -1;

        // 각 점에 대해, 기존 센터들에 대한 최소 거리 구하기
        for (int j = 0; j < n; ++j) {
            double minDist = numeric_limits<double>::max();

            // 이미 선택된 센터들과의 최소 거리 계산
            for (const auto& center : centers) {
                double dist = points[j].distance(center);
                minDist = min(minDist, dist);
            }

            // 최소 거리 중 가장 큰 값을 찾음
            if (minDist > maxMinDist) {
                maxMinDist = minDist;
                maxMinDistIndex = j;
            }
        }

        centers.push_back(points[maxMinDistIndex]);  // 가장 작은 최소 거리를 가진 점을 센터로 추가
    }

    // 각 점을 가장 가까운 센터로 분류
    for (int i = 0; i < n; ++i) {
        double minDist = points[i].distance(centers[0]);
        int clusterIndex = 0;

        for (int j = 1; j < k; ++j) {
            double dist = points[i].distance(centers[j]);
            if (dist < minDist) {
                minDist = dist;
                clusterIndex = j;
            }
        }

        clusters[clusterIndex].push_back(points[i]);
    }
}

// 파일에서 점들을 읽어오는 함수
void readPointsFromFile(const string& filename, vector<Point>& points) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
        return;
    }

    double x, y;
    set<Point> uniquePoints;  // 중복된 점을 제거하기 위해 set 사용

    while (file >> x >> y) {
        uniquePoints.insert(Point(x, y));
    }

    // 중복이 제거된 점들을 벡터에 추가
    points.assign(uniquePoints.begin(), uniquePoints.end());

    file.close();
}

int main() {
    string filename = "./clustering_input.txt"; // 파일 경로
    vector<Point> points;
    vector<Point> centers;
    vector<vector<Point>> clusters;

    // 파일에서 점들을 읽어옴
    readPointsFromFile(filename, points);

    // Approximate K-Clustering 수행
    int k = 8;  // 클러스터 개수
    approximateKClustering(points, k, centers, clusters);

    // 결과 출력
    cout << "클러스터 센터로 사용된 점들의 좌표:" << endl;
    for (const auto& center : centers) {
        cout << "(" << center.x << ", " << center.y << ")" << endl;
    }

    cout << "\n각 클러스터의 점들:" << endl;
    for (int i = 0; i < k; ++i) {
        cout << "\n클러스터 " << i + 1 << ":\n";
        for (const auto& point : clusters[i]) {
            cout << "(" << point.x << ", " << point.y << ")\n";
        }
    }

    return 0;
}
