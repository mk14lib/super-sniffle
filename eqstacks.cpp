#include <iostream>
#include <vector>
#include <numeric> // For std::accumulate
#include <algorithm> // For std::max

int main() {
    int n1, n2, n3;
    std::cin >> n1 >> n2 >> n3; // స్టాక్ సైజులను చదవండి

    // వెక్టర్స్‌లో సిలిండర్ ఎత్తులను నిల్వ చేయండి
    std::vector<int> h1(n1);
    std::vector<int> h2(n2);
    std::vector<int> h3(n3);

    // h1 కోసం ఇన్‌పుట్ చదవండి
    for (int i = 0; i < n1; ++i) {
        std::cin >> h1[i];
    }
    // h2 కోసం ఇన్‌పుట్ చదవండి
    for (int i = 0; i < n2; ++i) {
        std::cin >> h2[i];
    }
    // h3 కోసం ఇన్‌పుట్ చదవండి
    for (int i = 0; i < n3; ++i) {
        std::cin >> h3[i];
    }

    // ప్రతి స్టాక్ యొక్క ప్రస్తుత ఎత్తును లెక్కించండి
    long long sum1 = std::accumulate(h1.begin(), h1.end(), 0LL);
    long long sum2 = std::accumulate(h2.begin(), h2.end(), 0LL);
    long long sum3 = std::accumulate(h3.begin(), h3.end(), 0LL);

    // ప్రతి స్టాక్ కోసం ప్రస్తుత టాప్ సిలిండర్ ఇండెక్స్‌లను ట్రాక్ చేయడానికి పాయింటర్‌లు
    int top1 = 0;
    int top2 = 0;
    int top3 = 0;

    // అన్ని స్టాక్‌లు సమానమయ్యే వరకు లేదా ఏదైనా స్టాక్ ఖాళీ అయ్యే వరకు లూప్ చేయండి
    while (true) {
        // ఏదైనా స్టాక్ ఖాళీగా ఉంటే, వాటిని సమానం చేయలేము, కాబట్టి 0ని తిరిగి ఇవ్వండి
        if (top1 == n1 || top2 == n2 || top3 == n3) {
            std::cout << 0 << std::endl;
            return 0;
        }

        // స్టాక్‌ల ఎత్తులు ఇప్పటికే సమానంగా ఉంటే, ఆ ఎత్తునే సమాధానం
        if (sum1 == sum2 && sum2 == sum3) {
            std::cout << sum1 << std::endl;
            return 0;
        }

        // అత్యధిక ఎత్తు ఉన్న స్టాక్‌ను కనుగొని దాని టాప్ సిలిండర్‌ను తొలగించండి
        if (sum1 >= sum2 && sum1 >= sum3) {
            sum1 -= h1[top1];
            top1++;
        } else if (sum2 >= sum1 && sum2 >= sum3) {
            sum2 -= h2[top2];
            top2++;
        } else { // sum3 అత్యధికం
            sum3 -= h3[top3];
            top3++;
        }
    }

    return 0;
}
