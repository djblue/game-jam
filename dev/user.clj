(ns user)

(comment
  (require '[portal.api :as p])
  (p/open {:launcher :auto})
  (add-tap #'p/submit)
  (+ 1 2 3)
  comment)