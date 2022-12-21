//
//  MainTableViewController.m
//  LeanOpenGL
//
//  Created by hansen on 2022/10/20.
//

#import "MainTableViewController.h"
#import "OpenGLViewController.h"

@interface MainTableViewController ()

@property (strong, nonatomic) NSArray *items;

@end

@implementation MainTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.items = [[NSArray alloc] initWithObjects:
                  @"Triangle",
                  @"Container",
                  @"Box",
                  @"Illumination",
                  @"Nanosuit",
                  @"Breakout",
                  nil];
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:@"ID_CELL"];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.items.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"ID_CELL" forIndexPath:indexPath];
    
    cell.textLabel.text = [self.items objectAtIndex: indexPath.row];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSString *name = [self.items objectAtIndex:indexPath.row];
    OpenGLViewController *vc = [[OpenGLViewController alloc] initWithType:name];
    if (vc != nil) {
        [self.navigationController pushViewController:vc animated:YES];
    }
}

@end
