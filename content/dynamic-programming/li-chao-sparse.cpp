/**
 * Author: PedroGallo
 * Date: 18/10/2024
 * Description: Basic sparse Li-chao tree implementation, in which every node
 * in a segment tree contains the one needed line that has the min/max query
 * Time: O(\log{N}) for add-line(), query(); slow constant
 * Status: Tested (https://codeforces.com/gym/105257/problem/J)
*/


// line struct {ax + b} with {id} for max()
struct Line {
    int a, b, id;

    Line() {
        a = 0;
        b = -INF;
        id = -1;
    }

    Line(int a_, int b_, int id_ = 0) : a(a_), b(b_), id(id_) {}
    
    array<int, 2> operator()(int x){
        return {a*x + b, id};
    }
};

// Li Chao Tree for max() query 
struct Lichao {
    struct Node {
        Line line;
        int l, r;
 
        Node *left_node = nullptr;
        Node *right_node = nullptr;
    };
 
    Node* root = new Node;

    // lichao will cover range [l_, r_] and the initial default line is line_
    Lichao (int l_, int r_, Line line_ = Line()) {
        root->l = l_;
        root->r = r_;
        root->line = line_;
    }

    Node* add_line(Line new_line, Node *n) {
        if (!n) {
            Node *a = new Node;
            a->line = new_line;
            return a;
        }
 
        int l = n->l, r = n->r;
        int mid = (r+l)/2;
        
        if(new_line(mid) > n->line(mid)) {
            swap(new_line, n->line);
        }
 
        if(n->line(l) > new_line(l) and n->line(r) > new_line(r)) {
            return n;
        }
 
        if(new_line(l) > n->line(l)) {
            n->left_node = add_line(new_line, n->left_node);
            n->left_node->l = l;
            n->left_node->r = mid;
        }
        else {
            n->right_node = add_line(new_line, n->right_node);
            n->right_node->l = mid+1;
            n->right_node->r = r;
        }
 
        return n;
    }
    void add_line(Line new_line){
        add_line(new_line, root);
    }
 
    array<int, 2> query(int x, Node *n) {
        if(!n){
            return {-INF, -1};
        }

        int l = n->l, r = n->r;
        int mid = (r+l)/2;
 
        if(x <= mid){
            return max(n->line(x), query(x, n->left_node));
        }
        else{
            return max(n->line(x), query(x, n->right_node));
        }
    }
    array<int, 2> query(int x){
        return query(x, root);
    }
};