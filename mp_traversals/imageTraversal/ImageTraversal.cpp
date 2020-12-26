#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal_ = nullptr;
  current = Point(0, 0);
}

ImageTraversal::Iterator::Iterator(ImageTraversal * traversal, PNG & picture, Point & start, double & tolerance) {
  traversal_ = traversal;
  starting_point = start;
  tolerance_ = tolerance;
  picture_ = picture;
  current = traversal_->peek();
  visited.resize(picture_.width() * picture_.height(), false);
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if (!traversal_->empty()) {
    traversal_->pop();
    visited[current.x + current.y * picture_.width()] = true;

    Point right_ = Point(current.x + 1, current.y);
    Point below_ = Point(current.x, current.y + 1);
    Point left_ = Point(current.x - 1, current.y);
    Point above_ = Point(current.x, current.y - 1);

    while (!traversal_->empty() && pointVisited(Point(traversal_->peek().x, traversal_->peek().y))) {
      current = traversal_->pop();
    } 
    //check if point on the right of the current point is in the scope of the image
    if (right_.x < picture_.width() && right_.y < picture_.height()) {
      // check if point is in the scope of the given tolerance
      if (calculateDelta(picture_.getPixel(right_.x, right_.y), picture_.getPixel(starting_point.x, starting_point.y)) <= tolerance_ && !pointVisited(right_)) {
        traversal_->add(right_);
      }
    }
    //check if point below is in the scope of the image
    if (below_.x < picture_.width() && below_.y < picture_.height()) {
      // check if point is in the scope of the given tolerance
      if (calculateDelta(picture_.getPixel(below_.x, below_.y), picture_.getPixel(starting_point.x, starting_point.y)) <= tolerance_ && !pointVisited(below_)) {
        traversal_->add(below_);
      }
    }
    //check if point on the left of the current point is in the scope of the image
    if (left_.x < picture_.width() && left_.y < picture_.height()) {
      // check if point is in the scope of the given tolerance
      if (calculateDelta(picture_.getPixel(left_.x, left_.y), picture_.getPixel(starting_point.x, starting_point.y)) <= tolerance_ && !pointVisited(left_)) {
        traversal_->add(left_);
      }
    }
    //check if point above is in the scope of the image
    if (above_.x < picture_.width() && above_.y < picture_.height()) {
      // check if point is in the scope of the given tolerance
      if (calculateDelta(picture_.getPixel(above_.x, above_.y), picture_.getPixel(starting_point.x, starting_point.y)) <= tolerance_ && !pointVisited(above_)) {
        traversal_->add(above_);
      }
    }
    if (!traversal_->empty()) {
      current = traversal_->peek();
    }
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  //taken directly from lab trees TreeTraversals/TreeTraversals.h
  bool thisEmpty = false; 
  bool otherEmpty = false;

  if (traversal_ == NULL) { thisEmpty = true; }
  if (other.traversal_ == NULL) { otherEmpty = true; }

  if (!thisEmpty)  { thisEmpty = traversal_->empty(); }
  if (!otherEmpty) { otherEmpty = other.traversal_->empty(); }

  if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
  else if ((!thisEmpty)&&(!otherEmpty)) return (traversal_ != other.traversal_); //both not empty then compare the traversals
  else return true; // one is empty while the other is not, return true
}

bool ImageTraversal::Iterator::pointVisited(const Point & currPoint) const {
  return visited[currPoint.x + currPoint.y * picture_.width()];
}

