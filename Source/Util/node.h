//
//  node.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-17.
//
//

#ifndef node_h
#define node_h

#include "Blob.h"

#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <ostream>
#include <algorithm>

template<class POINT_PRECISION_T=float>
struct node{
    using point_value_type = POINT_PRECISION_T;
    using value_type = node;
    using node_ptr = std::shared_ptr<value_type>;
    using point_t = Point<POINT_PRECISION_T>;
    using blob_t = Blob<POINT_PRECISION_T>;
    
    enum label{
        black = 'b',
        white = 'w',
        root = 'r'
    };
private:
    enum{
        IN = '[',
        OUT = ']'
    };
    
    label lbl_;
    value_type* parent_;
    std::vector<node_ptr> childs_;
    std::vector<point_t> pos_;
public:
    node(label lbl = root, value_type* parent = nullptr) noexcept
        : lbl_{lbl}, parent_{parent}{
    }
    node(const std::string& tree) noexcept
        : lbl_{root}, parent_{nullptr}{
            set(tree);
            balance();
    }
    label getLabel()const noexcept{
        return lbl_;
    }
    std::string getTreeLabel()const noexcept{
        std::stringstream ss;
        auto i = std::begin(childs_);
        ss << getLabel();
        if(i != std::end(childs_)){
            ss << IN;
            std::for_each(i, std::end(childs_), [&](node_ptr n){
                ss << n->get()->getTreeLabel();
            });
            ss << OUT;
        }
        return ss.str();
    }
    auto getSubNodeSize() const noexcept -> decltype(childs_.size()){
        return childs_.size();
    }
    std::vector<node*> find(const std::string& tree)const noexcept{
        std::vector<node*> markers;
        findImp(tree.substr(2, tree.size() - 3), markers);
        return markers;
    }
    void setLabel(char c)noexcept{
        lbl_ = static_cast<label>(c);
    }
    void setLabel(label lbl)noexcept{
        lbl_ = lbl;
    }
    void setParent(value_type* parent)noexcept{
        parent_ = parent;
    }
    void addChildren(value_type* child)noexcept{
        child->setParent(this);
        childs_.emplace_back(std::make_shared(child));
    }
    void balance(){
        std::for_each(std::begin(childs_), std::end(childs_), [&](node_ptr ptr){
            ptr->get()->balance();
            std::qsort(&childs_[0], getSubNodeSize(), sizeof(node_ptr), value_type::compare);
        });
    }
    void fill(const point_t& p){
        pos_.emplace_back(p);
    }
    blob_t getCentroid()const noexcept{
        return blob_t{pos_};
    }
    friend std::ostream& operator<<(std::ostream& os, value_type* n){
        return os << n->getTreeLabel();
    }
private:
    static int compare(const void* a, const void* b){
        return ((node_ptr*)a)->get()->getSubNodeSize() -
               ((node_ptr*)b)->get()->getSubNodeSize();
    }
    void set(std::string& tree){
        if(!tree.empty()){
            unsigned char c = tree.front();
            tree.erase(0,1);
            switch(c){
                case IN:
                    childs_.back()->set(tree);
                    break;
                case OUT:
                    parent_->set(tree);
                    break;
                default:
                    addChildren(new value_type(c));
                    set(tree);
                    break;
            }
        }
    }
    void findImpl(const std::string& tree, std::vector<node*>& markers)const noexcept{
        const auto lbl = getTreeLabel();
        if(lbl == tree){
            markers.emplace_back(this);
        }
        else if(lbl.find(tree) != std::string::npos){
            std::for_each(std::begin(childs_), std::end(childs_),[&](node_ptr n){
                n->get()->findImpl(tree, markers);
            });
        }
    }
};

#endif /* node_h */
