#lang racket
(require 2htdp/batch-io)

(define lanternfish-contents (first (read-csv-file "day6.txt")))

;; Converts a list of "fish" into a dictionary containing the frequency of
;; fish that have a given timer state
;; Returns a hash-table with key: Natural, value: Natural
(define (fish-list->map contents)
  (cond [(empty? contents) (hash)]
        [(and (cons? contents) (string? (first contents)))
         (hash-update (fish-list->map (rest contents)) (string->number (first contents)) add1 0)]
        ))

(define (total-fish-population current-state) (foldr + 0 (hash-values current-state)))

;; Given the current state of the fish population, return a hash-table with the
;; state of all fish the next day
(define (next-state current-state)
  (define (process-frequencies frequency-list) 
    (cond [(empty? frequency-list) (hash)]
          [(cons? frequency-list)
           (let [
                 (key (car (first frequency-list)))
                 (value (cdr (first frequency-list)))
                 (new-hash (process-frequencies (rest frequency-list)))]
             (if (= key 0) ;; New fish are produced
                 (hash-update (hash-set new-hash 8 value) 6 (lambda (current) (+ current value)) 0)
                 (hash-update new-hash (sub1 key) (lambda (current) (+ current value)) 0)))]
          ))
  (process-frequencies (hash->list current-state))
  )

;; Runs the fish simulator as defined in AOC day 6
(define (fish-simulator init-state max-days)
  ;; Runs the simulator for a given day (current-day: Natural) given (current-state: hash)
  (define (simulate-on-day current-state current-day)
    (when (<= current-day max-days)
      (let [(new-generation (next-state current-state))]
        (begin
          (printf "After Day ~s:~n~s~nTotal Population ~s~n" current-day new-generation (total-fish-population new-generation))
          (simulate-on-day new-generation (add1 current-day)))
        )
      )
    )
 
  (begin
    (printf "Fish Simulator: ~nInitial State: ~s~n" init-state)
    (simulate-on-day init-state 1))
  )

(define initial-fish-population (fish-list->map lanternfish-contents))
(fish-simulator initial-fish-population 1000)