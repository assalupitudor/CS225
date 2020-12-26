/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

    if (first[curDim] < second[curDim]) { return true; }
    if (first[curDim] > second[curDim]) { return false; }
    return (first < second);
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

    double current_distance = 0;
    double potential_distance = 0;
    for (int i = 0; i < Dim; i++) { 
      current_distance += (currentBest[i] - target[i]) * (currentBest[i] - target[i]);
      potential_distance += (potential[i] - target[i]) * (potential[i] - target[i]);
    }
    if (potential_distance < current_distance) {
      return true; 
    }
    if (potential_distance > current_distance) {
      return false;
    }
    return potential < currentBest; 
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if (newPoints.size() == 0) {
      root = NULL;
    } else {
      for (const Point<Dim>& i: newPoints) {
        all_points.push_back(i);
      }
      root = createTree(0, newPoints.size()-1, 0);
    }

    
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  all_points = other.all_points;
  root = createTree(root, 0, all_points.size() - 1, 0);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  if(this != &rhs){
    delete *this;
    this = new KDTree(rhs);

  }

  return *this;
  
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  destroy(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return findNearestNeighbor(query,root,0);
}


template <int Dim>
void KDTree<Dim>::destroy(KDTreeNode *subroot) {
    if (!subroot) {
      return;
    }
    destroy(subroot->left);
    destroy(subroot->right);
    delete subroot;
}


template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::createTree(int begin, int end, int curDim) {
  if (begin > end) {
    return NULL;
  } else if (begin == end) {
    return new KDTreeNode(all_points[begin]);
  } else {
    int pivot_index = (begin + end)/2;
    quickSelect(begin, end, pivot_index, curDim);

    KDTreeNode * new_tree = new KDTreeNode(all_points[pivot_index]);
    new_tree->left = createTree(begin, (pivot_index - 1), (curDim + 1)%Dim);
    new_tree->right = createTree((pivot_index+1), end, (curDim + 1)%Dim);

    return new_tree;
  }
}

template <int Dim>
void KDTree<Dim>::quickSelect(int begin, int end, int pivot_index, int curDim) {
  while (begin != end) {
    Point<Dim> pivot_point = all_points[pivot_index];
    all_points[pivot_index] = all_points[end];
    all_points[end] = pivot_point;
    int new_index = begin;
    for (int i = begin; i < end; i++) {
      if (smallerDimVal(all_points[i], pivot_point, curDim) || all_points[i] == pivot_point) {
        Point<Dim> temp = all_points[new_index];
        all_points[new_index] = all_points[i];
        all_points[i] = temp;
        new_index++;
      }
    }
    Point<Dim> temp = all_points[new_index];
    all_points[new_index] = all_points[end];
    all_points[end] = temp;
    if (new_index == pivot_index){
      return;
    } else if (pivot_index < new_index) {
      end = new_index - 1;
    } else {
      begin = new_index + 1;
    }
      
  }
}

template<int Dim>
int KDTree<Dim>::distance(const Point<Dim>& point1,const Point<Dim>& point2)const {
  int distance = 0;
  for(int i = 0; i < Dim; i++)
    distance += (point1[i]-point2[i])*(point1[i]-point2[i]);
  return distance;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query,typename KDTree<Dim>::KDTreeNode* current_node, int curDim) const{
  if (current_node->left == NULL && current_node->right == NULL) {
    return current_node->point;
  }
   
  int nextDim=(curDim + 1)%Dim;
  Point<Dim> current_nearest = current_node->point;
  Point<Dim> potential_nearest = current_nearest;
  bool direction = smallerDimVal(query, current_nearest, curDim);
  if (direction && current_node->left!=NULL) {
    potential_nearest = findNearestNeighbor(query,current_node->left,nextDim);
  } else if (!direction && current_node->right!=NULL) {
    potential_nearest = findNearestNeighbor(query, current_node->right, nextDim);
  }

  if (shouldReplace(query, current_nearest, potential_nearest)) {
    current_nearest=potential_nearest;
  }
    
  int shortest_distance = distance(query, current_nearest);
  int dim_distance = (query[curDim] - current_node->point[curDim]) * (query[curDim] - current_node->point[curDim]);
  if(dim_distance <= shortest_distance) {
    if (!direction && current_node->left != NULL) {
      potential_nearest= findNearestNeighbor(query,current_node->left,nextDim);
      if (shouldReplace(query,current_nearest,potential_nearest))
        current_nearest=potential_nearest;
    }
    else if (direction && current_node->right != NULL) {
      potential_nearest= findNearestNeighbor(query, current_node->right, nextDim);
      if(shouldReplace(query,current_nearest,potential_nearest))
        current_nearest=potential_nearest;
    }
  }
  return current_nearest;
 }