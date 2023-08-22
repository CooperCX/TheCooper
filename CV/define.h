#include <vector>
#include <algorithm>

struct Box2i
{
    int left;
    int top;
    int right;
    int bot;
};

struct BBox
{
    Box2i roi;
    float confidence;
};

static float IoU(Box2i box1, Box2i box2) {
    int area1 = (box1.right - box1.left) * (box1.bot - box1.top);
    int area2 = (box2.right - box2.left) * (box2.bot - box2.top);

    int w = std::min(box1.right, box2.right) - std::max(box1.left, box2.left);
    int h = std::min(box1.bot, box2.bot) - std::max(box1.top, box2.top);

    if (w <= 0 || h <= 0) {
        return 0;
    }

    float intersect = w * h * 1.0f;
    float iou = intersect / (area1 + area2 + intersect);
}

static std::vector<BBox> nms(std::vector<BBox>& bboxes, float nmsThreshold) {
    std::vector<BBox> results;

    while (bboxes.size() > 0) {
        std::sort(bboxes.begin(), bboxes.end(), [](BBox b1, BBox b2){ return b1.confidence > b2.confidence; });
        results.push_back(bboxes[0]);

        for (int i = 1; i < bboxes.size(); i++) {
            float iou = IoU(bboxes[0].roi, bboxes[i].roi);
            if (iou > nmsThreshold) {
                bboxes.erase(bboxes.begin() + i);
            }
        }
        bboxes.erase(bboxes.begin());
    }

    return results;
}


struct Tensor {
    float *data = nullptr;

    int N = 0;
    int C = 0;
    int H = 0;
    int W = 0;

    float& at(int ni, int ci, int hi, int wi) {
        return data[W*(H*(C*ni+ci)+hi)+wi];
    }

    float at(int ni, int ci, int hi, int wi) const {
        return data[W*(H*(C*ni+ci)+hi)+wi];
    }
};

static Tensor Concat(const Tensor &a, const Tensor &b) {
    Tensor c = a;
    c.H = a.H + b.H;
    c.data = new float[c.N * c.C * c.H * c.W];

    for (int ni = 0; ni < a.N; ni++) {
        for (int ci = 0; ci < a.C; ci++) {
            for (int hi = 0; hi < a.H; hi++) {
                for (int wi = 0; wi < a.W; wi++) {
                    c.at(ni, ci, hi, wi) = a.at(ni, ci, hi, wi);
                }
            }
            for (int hi = 0; hi < b.H; hi++) {
                for (int wi = 0; wi < b.W; wi++) {
                    c.at(ni, ci, a.H + hi, wi) = b.at(ni, ci, hi, wi);
                }
            }
        }
    }
    return c;
}

// BN层