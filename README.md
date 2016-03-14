# Two-Factor Authentication Nudge

The TFA nudge module is an extension of TFA module. Its purpose is to show which users have two-factor authentication enabled and which users do not.

### Usage

- Create an extra field on you-site/admin/people that displays a boolean value representing which users have TFA

- Filter by that value

### Installation

 1. download and enable tfa_nudge and admin_views
 2. In your-site/admin/structure/views/view/admin_views_user/edit:

  * Add field: "Two-Factor Authentication: Two-Factor Security"
  * Add filter: "Two-Factor Authentication: Two-Factor Security"

This will create a field on your users table that displays an icon that indicates that user's TFA status. A lock icon indicates that TFA is enabled, a warning icon indicates that TFA is not enabled.

### Configuration

You can change the configuration in your-site/admin/structure/views/view/admin_views_user/edit to show an icon for TFA users only, non-TFA users only, display 'yes' or 'no', checks or x's, '1' or '0', etc. instead of icons.
