//
//  GeneratorViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 08/04/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit

class GeneratorPageViewController: UIPageViewController
{
    fileprivate lazy var pages: [UIViewController] = {
        return [
            self.getViewController(withIdentifier: "StyleViewId"),
            self.getViewController(withIdentifier: "InstrumentAccordsViewId"),
            self.getViewController(withIdentifier: "InstrumentArpegesViewId"),
            self.getViewController(withIdentifier: "InstrumentViewId"),
            self.getViewController(withIdentifier: "TempoViewId")
        ]
    }()
    
    fileprivate func getViewController(withIdentifier identifier: String) -> UIViewController
    {
        return UIStoryboard(name: "Main", bundle: nil).instantiateViewController(withIdentifier: identifier)
    }
    
    var pageControl = UIPageControl()
    
    override func viewDidLoad()
    {
        super.viewDidLoad()
        self.dataSource = self
        self.delegate   = self
        
        configurePageControl()
        if let firstVC = pages.first
        {
            setViewControllers([firstVC], direction: .forward, animated: true, completion: nil)
        }
    }
    
    func configurePageControl() {
        
        pageControl = UIPageControl(frame: CGRect(x: UIScreen.main.bounds.midX, y: UIScreen.main.bounds.midY - 380, width: 0, height: 100))
        
        self.pageControl.numberOfPages = pages.count
        self.pageControl.currentPage = 0
        self.pageControl.tintColor = Utils().uicolorFromHex(rgbValue: 0xFFFFFF)
        self.pageControl.pageIndicatorTintColor = Utils().uicolorFromHex(rgbValue: 0xFFFFFF)
        self.pageControl.currentPageIndicatorTintColor = Utils().uicolorFromHex(rgbValue: 0xD53972)
        self.view.addSubview(pageControl)
    }
}

extension GeneratorPageViewController: UIPageViewControllerDataSource
{
    func pageViewController(_ pageViewController: UIPageViewController, viewControllerBefore viewController: UIViewController) -> UIViewController? {
        
        guard let viewControllerIndex = pages.index(of: viewController) else { return nil }
        
        let previousIndex = viewControllerIndex - 1
        
        guard previousIndex >= 0          else { return nil }
        
        guard pages.count > previousIndex else { return nil        }
        
        return pages[previousIndex]
    }
    
    func pageViewController(_ pageViewController: UIPageViewController, viewControllerAfter viewController: UIViewController) -> UIViewController?
    {
        guard let viewControllerIndex = pages.index(of: viewController) else { return nil }
        
        let nextIndex = viewControllerIndex + 1
        
        guard nextIndex < pages.count else { return nil }
        
        guard pages.count > nextIndex else { return nil         }
        
        return pages[nextIndex]
    }
    // MARK: Delegate functions
    func pageViewController(_ pageViewController: UIPageViewController, didFinishAnimating finished: Bool, previousViewControllers: [UIViewController], transitionCompleted completed: Bool) {
        let pageContentViewController = pageViewController.viewControllers![0]
        self.pageControl.currentPage = pages.index(of: pageContentViewController)!
    }
}

extension GeneratorPageViewController: UIPageViewControllerDelegate { }
