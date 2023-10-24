#pragma once
#include <iterator>


namespace FilterIterator {

    template <class Predicate, class Iterator>
    class filter_iterator final {
    public:
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        using reference = typename std::iterator_traits<Iterator>::reference;
        using pointer = typename std::iterator_traits<Iterator>::pointer;
        using difference_type = typename std::iterator_traits<Iterator>::difference_type;
        using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;

        filter_iterator() = default;
        filter_iterator(Predicate f, const Iterator& first, const Iterator& end = Iterator()) : m_pred(f),
            m_first(first), m_end(end) {
            shift_iterator();
        };
       
        Predicate predicate() const {
            return m_pred;
        };
        Iterator end() const {
            return m_end;
        };
        Iterator const& base() const {
            return m_first;
        };
        reference operator*() const {
            return *m_first;
        };
        pointer operator->() const {
            return m_first;
        }
        difference_type operator-(const filter_iterator& other) const {
            return m_first - other.m_first;
        }
        bool operator==(const filter_iterator& other) const {
            return m_first == other.m_first;
        }
        bool operator!=(const filter_iterator& other) const {
            return m_first != other.m_first;
        }
        filter_iterator& operator++() {
            m_first++;
            shift_iterator();
            return *this;
        };
    private:
        Predicate m_pred;
        Iterator m_first;
        Iterator m_end;
        void shift_iterator() {
            while (m_first != m_end && !m_pred(*m_first)) {
                m_first++;
            }
        };
    };

    namespace CreatingFilterIterator {
        template <class Predicate, class Iterator>
        filter_iterator<Predicate, Iterator> make_filter_iterator(Predicate f, const Iterator& first, const Iterator& end = Iterator()) {
            return filter_iterator<Predicate, Iterator>(f, first, end);
        }
    }
    
}
