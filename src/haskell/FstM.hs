{-# LANGUAGE ExistentialQuantification #-}

module FstM where

myFst :: forall a b. (a, b) -> a
myFst (a, b) = a