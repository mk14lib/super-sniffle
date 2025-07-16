#include <iostream> // ఇన్పుట్/అవుట్పుట్ కార్యకలాపాల కోసం
#include <vector>   // వెక్టర్స్ (డైనమిక్ శ్రేణులు) ఉపయోగించడానికి
#include <algorithm> // సార్టింగ్ మరియు ప్రత్యేకమైన ఎలిమెంట్స్ కోసం

// Climbing the Leaderboard ఫంక్షన్
std::vector<int> climbingLeaderboard(std::vector<int> ranked, std::vector<int> player) {
    // లీడర్‌బోర్డ్‌లోని ప్రత్యేకమైన స్కోర్‌లను నిల్వ చేయడానికి ఒక వెక్టర్.
    // ర్యాంకింగ్‌లు ప్రత్యేకమైన స్కోర్‌లపై ఆధారపడి ఉంటాయి.
    std::vector<int> ranked_unique;

    // ranked వెక్టర్‌లోని డూప్లికేట్‌లను తొలగించి,
    // ప్రత్యేకమైన స్కోర్‌లను ranked_unique లోకి కాపీ చేయండి.
    // std::unique ఆనువైన ఎలిమెంట్లను వెనుకకు కదుపుతుంది, కానీ పరిమాణం మార్చదు.
    // కాబట్టి, దాని తర్వాత erase ఉపయోగించి డూప్లికేట్‌లను తొలగించాలి.
    if (!ranked.empty()) { // ranked ఖాళీగా లేదని నిర్ధారించుకోండి
        ranked_unique.push_back(ranked[0]); // మొదటి ఎలిమెంట్ ఎప్పుడూ ప్రత్యేకమైనది
        for (size_t i = 1; i < ranked.size(); ++i) {
            if (ranked[i] != ranked[i-1]) { // ప్రస్తుత స్కోర్ మునుపటి దాని కంటే భిన్నంగా ఉంటే
                ranked_unique.push_back(ranked[i]); // ప్రత్యేకమైనదిగా జోడించండి
            }
        }
    }

    // అలైస్ యొక్క ర్యాంకులను నిల్వ చేయడానికి ఒక వెక్టర్.
    std::vector<int> alice_ranks;

    // లీడర్‌బోర్డ్‌లోని ప్రత్యేకమైన స్కోర్‌ల సంఖ్య.
    int n = ranked_unique.size();
    // లీడర్‌బోర్డ్‌ను వెనుక నుండి పోల్చడానికి ఒక పాయింటర్.
    // ఇది చివర (తక్కువ ర్యాంక్) నుండి మొదలవుతుంది.
    int j = n - 1;

    // అలైస్ యొక్క ప్రతి స్కోర్‌ను పరిశీలించండి.
    // అలైస్ స్కోర్‌లు పెరుగుతున్న క్రమంలో (ascending order) ఉంటాయి.
    for (int score : player) {
        // అలైస్ యొక్క ప్రస్తుత స్కోర్ లీడర్‌బోర్డ్‌లోని ప్రస్తుత స్కోర్ (ranked_unique[j])
        // కంటే ఎక్కువ లేదా సమానంగా ఉన్నంత వరకు లీడర్‌బోర్డ్‌లో పైకి వెళ్ళండి.
        // అంటే, అలైస్ ర్యాంక్ మెరుగుపడటానికి అవకాశం ఉంది.
        while (j >= 0 && score >= ranked_unique[j]) {
            j--; // ర్యాంకును మెరుగుపరుచుకోవడానికి లీడర్‌బోర్డ్‌లో పైకి కదలండి.
        }

        // లూప్ పూర్తయిన తర్వాత, j లీడర్‌బోర్డ్‌లో అలైస్ ఎక్కడ ఉంటుందో సూచిస్తుంది.
        // j + 1 అనేది ఆమె ర్యాంక్.
        // ఉదాహరణకు, j = -1 అయితే, అలైస్ అందరి కంటే మెరుగైనది, ఆమె ర్యాంక్ 1.
        // j = 0 అయితే, ఆమె ranked_unique[0] తర్వాత ఉంది, అంటే ఆమె ర్యాంక్ 2.
        // n అనేది ప్రత్యేకమైన ర్యాంకుల సంఖ్య.
        // కాబట్టి, లీడర్‌బోర్డ్‌లో లేని స్కోర్‌ల కోసం (అన్నింటికంటే తక్కువ),
        // ర్యాంక్ n + 1 అవుతుంది.
        alice_ranks.push_back(j + 2);
    }

    return alice_ranks;
}

int main() {
    // ఉదాహరణ 1
    std::vector<int> ranked_scores = {100, 90, 90, 80, 75, 60};
    std::vector<int> player_scores = {50, 65, 77, 90, 102};

    std::vector<int> result = climbingLeaderboard(ranked_scores, player_scores);

    std::cout << "అలైస్ యొక్క ర్యాంకులు: ";
    for (int rank : result) {
        std::cout << rank << " ";
    }
    std::cout << std::endl;
    // అంచనా అవుట్‌పుట్: 6 5 4 2 1

    std::vector<int> ranked_scores_2 = {100, 100, 50, 40, 40, 20, 10};
    std::vector<int> player_scores_2 = {5, 25, 50, 120};
    std::vector<int> result_2 = climbingLeaderboard(ranked_scores_2, player_scores_2);

    std::cout << "అలైస్ యొక్క ర్యాంకులు (ఉదాహరణ 2): ";
    for (int rank : result_2) {
        std::cout << rank << " ";
    }
    std::cout << std::endl;
    // అంచనా అవుట్‌పుట్: 6 4 2 1

    return 0;
}
