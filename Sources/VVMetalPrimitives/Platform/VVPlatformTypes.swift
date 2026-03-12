import Foundation

#if canImport(AppKit)
import AppKit
public typealias VVColor = NSColor
public typealias VVFont = NSFont
#else
import UIKit
public typealias VVColor = UIColor
public typealias VVFont = UIFont
#endif
