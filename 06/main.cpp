#include <iostream>
#include <queue>
#include <utility>

// 6_4
// Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
// Требуется построить бинарное дерево, заданное наивным порядком вставки.
// Выведите элементы в порядке level-order (по слоям, “в ширину”).

template <typename T>
class TreeNode {
private:
    T element;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
    std::function<bool (int, int)> comp;

public:
    TreeNode(T root_element, std::function<bool (int, int)> comp) :
        element(root_element),
        comp(std::move(comp))
        {}

    void Append(T new_element) {
        TreeNode *current_node = this;

        while (current_node != nullptr) {
            bool to_left = comp(new_element, current_node->element);

            TreeNode *next_node = to_left ? current_node->left : current_node->right;
            if (next_node == nullptr) {
                next_node = new TreeNode<T>(new_element, comp);
                if (to_left) {
                    current_node->left = next_node;
                } else {
                    current_node->right = next_node;
                }
                break;
            }
            current_node = next_node;
        }
    }

    std::string GetLevelOrderView() {
        // Была информация, что с 3-го задания допускается использовать std-коллекции
        auto *node_queue = new std::queue<TreeNode*>();

        node_queue->push(this);

        std::string result;
        while (!node_queue->empty()) {
            TreeNode *current_node = node_queue->front();
            node_queue->pop();

            if (current_node->left) {
                node_queue->push(current_node->left);
            }

            if (current_node->right) {
                node_queue->push(current_node->right);
            }

            result += std::to_string(current_node->element);
            if (!node_queue->empty()) {
                result += " ";
            }
        }

        return result;
    }
};

int main() {
    int n;
    std::cin >> n;

    if (n == 0) {
        return 1;
    }

    int root_element;
    std::cin >> root_element;
    auto *root = new TreeNode<int>(root_element, [] (const auto& first, const auto& last) {
        return first < last;
    });

    for (int i = 1; i < n; i++) {
        int new_element;
        std::cin >> new_element;
        root->Append(new_element);
    }

    std::cout << root->GetLevelOrderView();

    return 0;
}
